#include "include/tetromino.h"
#include "include/common.h"
#include "include/board.h"
#include <stdlib.h>

// 전역 변수 정의
int block_number      = 0;
int next_block_number = 0;
int block_state       = 0;
int x = 3, y = 0;
int best_point = 0;
long point     = 0;


void init_tetromino(void) {
    next_block_number = rand() % 7;
    spawn_new_block();
}

/* 현재 블록 = next, 위치/회전 초기화 후 충돌 검사 → 다음 블록 생성 */
void spawn_new_block(void) {
    block_number = next_block_number;
    block_state  = LEFT; // 초기 회전 상태
    x = 3; y = 0; // 초기 위치

    // 스폰 시 충돌이 일어나면 게임 종료
    if (is_collision(block_number, block_state, x, y)) {
        game = GAME_END;
    }
    // 다음 블록 난수
    next_block_number = rand() % 7;
}

void move_left(void) {
    if (!is_collision(block_number, block_state, x - 1, y))
        x--;
}


void move_right(void) {
    if (!is_collision(block_number, block_state, x + 1, y))
        x++;
}
void move_down(void) {}
void rotate_block(void) {
    int new_state = (block_state + 1) % 4;
    if (!is_collision(block_number, new_state, x, y)) {
        block_state = new_state;
        return;
    }
    // wall kick 기능 추가
    if (!is_collision(block_number, new_state, x - 1, y)) {
        x = x - 1;
        block_state = new_state;
        return;
    }
    if (!is_collision(block_number, new_state, x + 1, y)) {
        x = x + 1;
        block_state = new_state;
        return;
    }

}
void drop_to_bottom(void) {}