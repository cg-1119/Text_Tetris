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
void move_down(void) {
    if (!is_collision(block_number, block_state, x, y + 1))
        y++;
    else {
        fix_block(block_number, block_state, x, y);
        // TODO 한 줄이 찼으면 지우는 로직 추가
        clear_full_line();   
        spawn_new_block();
    }
}
void rotate_block(void) {
    int new_state = (block_state + 1) % 4;
    if (!is_collision(block_number, new_state, x, y)) {
        block_state = new_state;
        return;
    }
    // wall kick 기능 추가 (x 축만)
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
void drop_to_bottom(void) {
    while (!is_collision(block_number, block_state, x, y + 1)) {
        y++;
    }
    fix_block(block_number, block_state, x, y);
    clear_full_line();   
    spawn_new_block();
}