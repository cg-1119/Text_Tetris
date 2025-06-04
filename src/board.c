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

bool is_collision(int type, int rotation, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (all_blocks[type][rotation][row][col]) {
                int board_row = y + row;
                int board_col = x + col;

                // 1) 좌, 우 벽 충돌 검사
                if (board_col < 1 || board_col >= 9) {
                    return true;
                }
                // 2) 바닥 검사
                if (board_row >= 21) {
                    return true;
                }
                // 4) 다른 블록 충돌 검사
                if (tetris_table[board_row][board_col] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}
