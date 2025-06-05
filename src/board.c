#include "include/board.h"
#include "include/config.h"

void init_board(void) {
    int row, col;
    for (row = 0; row < BOARD_ROWS; row++) {
        for (col = 0; col < 10; col++) {
            tetris_board[row][col] = 0;
        }
    }
    // 좌우 벽
    for (row = 2; row < BOARD_ROWS; row++) {
        tetris_board[row][0] = 1;
        tetris_board[row][9] = 1;
    }
    // 벽, 바닥
    for (col = 0; col < BOARD_COLS; col++) {
        tetris_board[20][col] = 1;
    }
}
bool is_collision(Tetromino type, int rotation, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[type][rotation][row][col]) {
                int board_row = y + row;
                int board_col = x + col;

                // 1) 좌, 우 벽 충돌 검사
                if (board_col < 1 || board_col >= 9) {
                    return true;
                }
                // 2) 바닥 검사
                if (board_row >= 20) {
                    return true;
                }
                // 3) 다른 블록 충돌 검사
                if (tetris_board[board_row][board_col] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void fix_block(Tetromino type, int rotation, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[type][rotation][row][col]) {
                int board_row = y + row;
                int board_col = x + col;
                // 유효한 공간에 존재하면 블럭 고정
                if (board_row >= 0 && board_row < 21 && board_col >= 0 && board_col < 10) {
                    tetris_board[board_row][board_col] = 1;
                }
            }
        }
    }
}

int clear_full_line(void) {
    int clear_line = 0;
    bool is_full;
    for (int row = BOARD_ROWS - 2; row >= 2; row--) {
        is_full = true;
        for (int col = 1; col < 9; col++) {
            if (tetris_board[row][col] != 1){
                is_full = false;
                break;
            }
        }
        // if_full = true라면 현재 row 기준으로 이전 인덱스들을 한 칸 당김
        if (is_full) {
            clear_line++;
            for (int r = row; r >= 1; r--) {
                for (int c = 1; c < 9; c++) {
                    tetris_board[r][c] = tetris_board[r - 1][c];

                }
            }
            // 현재 row의 데이터는 이전 인덱스의 row에서 가져왔으므로 인덱스도 이전으로 되돌려야 모든 열 검사 가능
            row++;
        }
    }
    return clear_line;
}


