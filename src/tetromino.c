#include "include/tetromino.h"
#include "include/common.h"
#include "include/board.h"
#include <stdlib.h>
#include <time.h>

// 전역 변수 정의
int block_number      = 0;
int next_block_number = 0;
int block_state       = 0;
int x = 3, y = 0;
int best_point = 0;
long point     = 0;


void init_tetromino(void) {
    srand(time(NULL));
    next_block_number = rand() % 7;
    spawn_new_block();
}

/* 현재 블록 = next, 위치/회전 초기화 후 충돌 검사 → 다음 블록 생성 */
void spawn_new_block(void) {
    block_number = next_block_number;
    block_state  = 0; /* 초기 회전 상태 = 0 */
    x = 3; y = 0;    /* 초기 스폰 위치 */

    /* 스폰 직후 충돌 시 게임 종료 */
    if (is_collision(block_number, block_state, x, y)) {
        game = GAME_END;
    }
    /* 다음 블록 난수 생성 */
    next_block_number = rand() % 7;
}

/* 왼쪽 이동 */
void move_left(void) {
    if (!is_collision(block_number, block_state, x - 1, y)) {
        x--;
    }
}

/* 오른쪽 이동 */
void move_right(void) {
    if (!is_collision(block_number, block_state, x + 1, y)) {
        x++;
    }
}
void move_down(void) {}
void rotate_block(void) {}
void drop_to_bottom(void) {}