#include "include/render.h"
#include "include/common.h"
#include <stdio.h>

// 블록
char i_block[4][4][4] = {
    { {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0} },
    { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {1,1,1,1} },
    { {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} },
    { {1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }
};
char t_block[4][4][4] = {
    {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
    {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{0,0,1,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}}
};
char s_block[4][4][4] = {
    {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
    {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}}
};
char z_block[4][4][4] = {
    {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
    {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
    {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}
};
char l_block[4][4][4] = {
    {{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},
    {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
    {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}}
};
char j_block[4][4][4] = {
    {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},
    {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}},
    {{0,0,0,0},{0,0,0,0},{1,1,1,0},{0,0,1,0}}
};
char o_block[4][4][4] = {
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
};

char tetris_table[21][10];
char (*all_blocks[7])[4][4] = {
    i_block, t_block, s_block, z_block, l_block, j_block, o_block
};

void draw_screen(void) {
    // ANSI Escape로 화면 제어
    printf("\x1b[3J");
    printf("\x1b[2J");
    printf("\x1b[H");

    draw_board();
    draw_tetromino();
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
            if (all_blocks[block_number][block_state][row][col]) {
                int board_row = y + row;
                int board_col = x + col;
                printf("\x1b[%d;%dH", board_row + 1, board_col * 2 + 1);
                printf("[]");
            }
        }
    }
}
void draw_next_block(void) {
    printf("\x1b[%d;%dH", 1, 26);
    printf("Next");
    printf("\x1b[%d;%dH", 2, 22);
    printf("+------------+");
    for (int r = 3; r <= 7; r++) {
        printf("\x1b[%d;%dH", r, 22);
        printf("|            |");
    }
    printf("\x1b[%d;%dH", 8, 22);
    printf("+------------+");

    // 2) 다음 블록 모양을 4×4 그리드로 순회하면서 출력
    //    회전 상태는 0으로 고정(Spawn 시 모양). 필요시 다른 상태를 넣어도 됩니다.
    int next_type = next_block_number;
    int rot = 0; // 미리보기는 회전 상태 0(= spawn 기본)으로 가정

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (all_blocks[next_type][rot][row][col]) {
                // board_row: 실제 콘솔 행 = NEXT_ROW_OFFSET + row
                // board_col: 실제 콘솔 열 = NEXT_COL_OFFSET + col*2
                int board_row = 4 + row;
                int board_col = 27 + col * 2;
                printf("\x1b[%d;%dH", board_row, board_col);
                printf("[]");
            }
        }
    }
}