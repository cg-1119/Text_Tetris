#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/board.h"
#include "include/input.h"
#include "include/render.h"
#include "include/tetromino.h"

int game = GAME_END;

int display_menu(void)
{
    int menu = 0;

    while (1)
    {
        system("clear");
        printf("\n\n\t\t\t\tText Tetris\n");
        printf("\t\t\t============================\n");
        printf("\t\t\t\tGAME MENU\n");
        printf("\t\t\t============================\n");
        printf("\t\t\t   1) Game Start\n");
        printf("\t\t\t   2) Search history\n");
        printf("\t\t\t   3) Record Output\n");
        printf("\t\t\t   4) QUIT\n");
        printf("\t\t\t============================\n");
        printf("\t\t\t\t\t SELECT : ");

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
    init_board();
    init_tetromino();

    // 게임 루프
    while (game == GAME_START) {
        int key = get_key();
        if (key) {
            // 눌린 키가 있을 때만 처리
            if (key == 'j' || key == 'J')
                move_left();
            else if (key == 'l' || key == 'L')
                move_right();
            // else if (key == 'k' || key == 'K')
            //     move_down();
            // else if (key == 'i' || key == 'I')
            //     rotate_block();
            // else if (key == 'a' || key == 'A')
            //     drop_to_bottom();
            else if (key == 'p' || key == 'P')
                game = GAME_END;
        }
        draw_screen();
        usleep(50000);
    }
    restore_terminal();
    return 1;
}

void search_result(void)
{
    /* TODO: 기록 검색 로직 구현 (빈 틀) */
}

void print_result(void)
{
    /* TODO: 모든 기록 출력 로직 구현 (빈 틀) */
}