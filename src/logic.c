#include "include/config.h"
#include "include/table.h"
#include "include/input.h"
#include "include/render.h"
#include "include/tetromino.h"
#include "include/point.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


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
    gettimeofday(&prev_time, NULL);

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
                gettimeofday(&prev_time, NULL);
            }
            else if (key == 'i' || key == 'I')
                rotate_block();
            else if (key == 'a' || key == 'A') {
                drop_to_bottom();
                gettimeofday(&prev_time, NULL);
            }
            else if (key == 'p' || key == 'P')
                game = GAME_END;
        }
        // 자동 낙하 계산
        gettimeofday(&curr_time, NULL);
        long elapsed = time_diff_ms(&prev_time, &curr_time);
        if (elapsed >= drop_ms) {
            move_down();
            gettimeofday(&prev_time, NULL); // 자동 낙하 후 기준 시각을 현재 시각으로 재설정
        }


        draw_game_screen();
        usleep(50000);
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

    // 이름이 입력되지 않으면 Anonymous로 저장
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // fgets는 맨 끝에 \n을 포함하기 때문에 제거
        name[strcspn(name, "\n")] = '\0';
        if (name[0] == '\0') {
            strcpy(name, "Anonymous");
        }
    } else {
        strcpy(name, "Anonymous");
    }
    save_point_to_list(name);
    fflush(stdout);
    return GAME_END;
}

void search_result(void)
{
    draw_search_page();
    printf("\x1b[%d;%dH", 11, 22);
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
            usleep(50 * 1000);
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