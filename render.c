#include "include/render.h"
#include "include/common.h"
#include <stdio.h>

char tetris_table[21][10];

void draw_board(void) {
    // ANSI Escape로 화면 제어
    printf("\x1b[2J"); // 화면 지우기
    printf("\x1b[H");
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
    fflush(stdout);
}
