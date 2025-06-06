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
    ExceptionCode exception;
    // load_point 에러처리
    if (load_point() == SAVE_FILE_EXCEPTION) {
        draw_savefile_exception_message();
        getchar();
        exit(EXIT_FAILURE);
    }
 
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

    const long drop_ms = 500; // 블록 자동으로 떨어지는 간격 = 0.5초
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
    // 커서를 적절한 위치로 옮김
    printf("\x1b[%d;%dH", 11, 22);
    fflush(stdout);

    char name[30];
    int ch;
    // 버퍼 비우기
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (fgets(name, sizeof(name), stdin) != NULL) {
        // fgets는 맨 끝에 \n을 포함하기 때문에 제거
        name[strcspn(name, "\n")] = '\0';
        if (name[0] == '\0') {
            strcpy(name, "Anonymous");
        }
    } else {
        strcpy(name, "Anonymous");
    }
    save_point(name);
    fflush(stdout);
    return GAME_END;
}

void search_result(void)
{
    /* TODO: 기록 검색 로직 구현 (빈 틀) */
}

void print_result(void)
{
    /* TODO: 모든 기록 출력 로직 구현 (빈 틀) */
}