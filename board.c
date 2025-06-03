#include "include/board.h"
#include "include/common.h"

char tetris_table[21][10];

void init_board(void) {
    int row, col;
    for (row = 0; row < 21; row++) {
        for (col = 0; col < 10; col++) {
            tetris_table[row][col] = 0;
        }
    }
    // 좌우 벽
    for (row = 2; row < 21; row++) {
        tetris_table[row][0] = 1;
        tetris_table[row][9] = 1;
    }
    // 벽, 바닥
    for (col = 0; col < 10; col++) {
        tetris_table[20][col] = 1;
    }
}
