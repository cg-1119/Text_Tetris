#include "include/config.h"
#include "include/table.h"
#include "include/input.h"
#include "include/render.h"
#include "include/tetromino.h"
#include "include/point.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  // Windows에 없는 timeval 구현
  struct timeval {
      long tv_sec;   // seconds
      long tv_usec;  // microseconds
  };

  static void sleep_ms(int ms) {
      Sleep(ms);
  }
  static void get_time_of_day(struct timeval *tv) {
      FILETIME ft;
      ULARGE_INTEGER uli;
      GetSystemTimeAsFileTime(&ft);
      uli.LowPart  = ft.dwLowDateTime;
      uli.HighPart = ft.dwHighDateTime;

      // Windows epoch → Unix epoch
      // 100-ns 단위를 μs 단위로 변환(나누기 10)
      uint64_t usec = (uli.QuadPart - 116444736000000000ULL) / 10;
      tv->tv_sec  = (long)(usec / 1000000ULL);
      tv->tv_usec = (long)(usec % 1000000ULL);
  }

#else
  #include <unistd.h>
  #include <sys/time.h>
  static void sleep_ms(int ms) {
      usleep(ms * 1000);
  }
   static void get_time_of_day(struct timeval *tv) {
      gettimeofday(tv, NULL);
  }
#endif


// 시간 비교 헬퍼 함수
static long time_diff_ms(struct timeval *start, struct timeval *end) {
    long secs  = end->tv_sec  - start->tv_sec;
    long usecs = end->tv_usec - start->tv_usec;
    return secs * 1000 + usecs / 1000;
}


int display_menu(void)
{
    int menu = 0;
 
    while (true)
    {
        draw_main_menu();
        // 입력이 숫자가 아닌 경우
        if (scanf("%d", &menu) != 1) {
            // 버퍼를 비우고 continue
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        // 잘못된 숫자가 입력된 경우
        if (menu < 1 || menu > 4) {
            continue;
        }

        return menu;
    }
}

int game_start(void)
{
    setup_terminal();
    init_table();
    init_tetromino();

    const long drop_ms = 700; // 블록 자동으로 떨어지는 간격 = 0.7초
    struct timeval prev_time, curr_time;
    get_time_of_day(&prev_time);

    // 게임 루프
    while (game == GAME_START) {
        int key = get_key();
        if (key) {
            // 눌린 키가 있을 때만 처리
            if (key == 'j' || key == 'J')
                move_left();
            else if (key == 'l' || key == 'L')
                move_right();
            else if (key == 'k' || key == 'K') {
                // 직접 다운을 했으면 타이머 리셋
                move_down();
                get_time_of_day(&prev_time);
            }
            else if (key == 'i' || key == 'I')
                rotate_block();
            else if (key == 'a' || key == 'A') {
                drop_to_bottom();
                get_time_of_day(&prev_time);
            }
            else if (key == 'p' || key == 'P')
                game = GAME_END;
        }
        // 자동 낙하 계산
        get_time_of_day(&curr_time);
        long elapsed = time_diff_ms(&prev_time, &curr_time);
        if (elapsed >= drop_ms) {
            move_down();
            get_time_of_day(&prev_time); // 자동 낙하 후 기준 시각을 현재 시각으로 재설정
        }


        draw_game_screen();
        sleep_ms(50); // 프레임 딜레이
    }
    restore_terminal();
    draw_game_over();
    // 0 포인트는 기록 미지원
    if (!point) {
         int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        getchar();
        return GAME_END;
    }
    // 커서를 적절한 위치로 옮김
    printf("\x1b[%d;%dH", 11, 22);
    fflush(stdout);

    char name[30];
    int ch;
    // 버퍼 비우기
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (fgets(name, sizeof(name), stdin) != NULL)
        name[strcspn(name, "\n")] = '\0'; // 개행문자 null로 교체

    // 입력이 없으면 저장 x
    if (name[0] != '\0') {
        save_point_to_list(name);
        save_point_to_file();
    }
    else // 포인트 초기화
        point = 0;
    

    fflush(stdout);
    return GAME_END;
}

void search_result(void)
{
    draw_search_page();

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    char query[30];
    printf("\x1b[%d;%dH", 9, 31);
    fflush(stdout);

    if (!fgets(query, sizeof(query), stdin)) return;
    query[strcspn(query, "\n")] = '\0';

    if (query[0] == '\0') return;

    draw_search_results(query);
    getchar();
}

void print_result(void)
{
    setup_terminal();
    int total_pages = (list_length + 4) / 5;
    int current_page = 0;
    draw_record_page(current_page);

    // total_pages가 0이면 종료
    if (total_pages == 0) {
        int ch;
        restore_terminal();
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        getchar();
        return;
    }

    while (true) {
        int key = get_key();
        if (!key) {
            // 키 입력이 없으면 loop를 잠깐 쉬었다가 다시 확인
            sleep_ms(50);
            continue;
        }

        if (key == 'l' || key == 'L') {
            // 다음 페이지로 (마지막이 아니면)
            if (current_page < total_pages - 1) {
                current_page++;
                draw_record_page(current_page);
            }
        }
        else if (key == 'j' || key == 'J') {
            // 이전 페이지로 (첫 페이지가 아니면)
            if (current_page > 0) {
                current_page--;
                draw_record_page(current_page);
            }
        }
        else if (key == 'p' || key == 'P') break;
    }
    restore_terminal();
}