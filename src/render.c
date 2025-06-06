#include "include/render.h"
#include "include/config.h"
#include "include/type.h"

#include <stdio.h>

void draw_main_menu(void) {
    printf("\x1b[2J");
    printf("\x1b[H");
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
}

void draw_game_screen(void) {
    // ANSI Escape로 화면 제어
    printf("\x1b[3J");
    printf("\x1b[2J");
    printf("\x1b[H");

    draw_board();
    draw_tetromino();
    draw_point();
    draw_next_block();
    
    fflush(stdout);
}
void draw_board(void) {
    for (int row = 0; row < 21; row++) {
        for (int col = 0; col < 10; col++) {
            if (tetris_table[row][col] == 1) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}
void draw_tetromino(void) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[block_number][block_state][row][col]) {
                int table_row = y + row;
                int table_col = x + col;
                printf("\x1b[%d;%dH", table_row + 1, table_col * 2 + 1);
                printf("[]");
            }
        }
    }
}
void draw_point(void) {
    printf("\x1b[%d;%dH", 1, 22);
    printf("Best Point : %d", best_point);
    printf("\x1b[%d;%dH", 2, 22);
    printf("Point : %ld", point);
}

void draw_next_block(void) {
    printf("\x1b[%d;%dH", 5, 27);
    printf("Next");
    printf("\x1b[%d;%dH", 6, 22);
    printf("+------------+");
    for (int r = 7; r <= 11; r++) {
        printf("\x1b[%d;%dH", r, 22);
        printf("|            |");
    }
    printf("\x1b[%d;%dH", 12, 22);
    printf("+------------+");

    int next_type = next_block_number;
    // 블록 출력
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[next_type][block_state][row][col]) {
                int table_row = 8 + row;
                int table_col = 27 + col * 2;
                printf("\x1b[%d;%dH", table_row, table_col);
                printf("[]");
            }
        }
    }
}

void draw_game_over(void) {
    printf("\x1b[%d;%dH", 7, 1);
    printf("+==============================+\n");
    printf("|           Game Over          |\n");       
    printf("+==============================+\n");
    printf("|        your point: %ld         |\n", point);
    printf("|   Input your name:           |\n");
    printf("+==============================+");
    fflush(stdout);
}

void draw_savefile_exception_message(void) {
    printf("Unable to load save file. Please delete ‘points.txt’ and restart the application\n");
    printf("Press Enter key to exit program.");
}