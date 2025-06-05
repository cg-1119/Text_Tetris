#include "include/tetromino.h"
#include "include/config.h"
#include "include/board.h"
#include "include/point.h"

#include <stdlib.h>

// ------------------------------------------------------------------
// 블록들의 순서를 저장하기 위해 큐를 사용하였습니다.
// bagQueue에는 0에서 7까지의 숫자를 무작위로 집어넣어 다음 블록을 꺼내쓰고
// 만약 bagQueue가 비어진다면, shuffle_bag를 호출하여 블럭들의 순서를 저장합니다.
// ------------------------------------------------------------------

typedef struct BlockQueue_{
    int data[TETROMINO_COUNT];
    int head;
    int tail;
    int count;
} BlockQueue;

// 파일 내 전역변수로 사용
static BlockQueue bagQueue;

static void set_queue(BlockQueue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;

}
static bool is_empty_queue(BlockQueue *q) {
    return (q->count == 0);
}
static bool is_full_queue(BlockQueue *q) {
    return (q->count == TETROMINO_COUNT);
}
/* 성공 여부를 bool형으로 반환합니다.*/
static bool enqueue(BlockQueue *q, Tetromino type) {
    if (is_full_queue(q))
        return false;

    q->data[q->tail] = type;   
    q->tail = (q->tail + 1) % TETROMINO_COUNT;
    q->count++;
    return true;
}
/// @brief 성공 여부를 bool형으로 반환합니다.
/// @param q bagQueue
/// @param out 출력으로 받을 다음 블록
static bool dequeue(BlockQueue *q, Tetromino *out) {
    if (is_empty_queue(q))
        return false;

    *out = q->data[q->head];
    q->head = (q->head + 1) % TETROMINO_COUNT;
    q->count--;
    return true;
}
// 가방 크기만큼의 무작위 숫자 배열을 생성하여 enqueue 합니다.
static void shuffle_bag(void) {
    int temp[7];
    for (int i = 0; i < TETROMINO_COUNT; i++) {
        temp[i] = i;
    }

    // 셔플
    for (int i = 7 - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
    }

    // 셔플된 순서대로 enqueue
    set_queue(&bagQueue);
    for (int i = 0; i < TETROMINO_COUNT; i++) {
        enqueue(&bagQueue, temp[i]);
    }
}
// ------------------------------------------------------------------

void init_tetromino(void) {
    shuffle_bag();
    dequeue(&bagQueue, &next_block); // 다음 블록을 큐에서 꺼내 저장
    spawn_new_block();
}   

void spawn_new_block(void) {
    current_block = next_block;
    block_state  = LEFT; // 초기 회전 상태
    x = 3; y = 0; // 초기 위치

    // 스폰 시 충돌이 일어나면 게임 종료
    if (is_collision(current_block, block_state, x, y)) {
        game = GAME_END;
    }
    // 큐가 비었다면 다시 채우기
    if (is_empty_queue(&bagQueue)) {
        shuffle_bag();
    }
    dequeue(&bagQueue, &next_block);
}

void move_left(void) {
    if (!is_collision(current_block, block_state, x - 1, y))
        x--;
}


void move_right(void) {
    if (!is_collision(current_block, block_state, x + 1, y))
        x++;
}
void move_down(void) {
    if (!is_collision(current_block, block_state, x, y + 1))
        y++;
    else {
        fix_block(current_block, block_state, x, y);
        clear_lines = clear_full_line();
        point += point_for_line(clear_lines);
        spawn_new_block();
    }
}
void rotate_block(void) {
    int new_state = (block_state + 1) % 4;
    if (!is_collision(current_block, new_state, x, y)) {
        block_state = new_state;
        return;
    }
    // wall kick 기능 추가 (x 축만)
    if (!is_collision(current_block, new_state, x - 1, y)) {
        x = x - 1;
        block_state = new_state;
        return;
    }
    if (!is_collision(current_block, new_state, x + 1, y)) {
        x = x + 1;
        block_state = new_state;
        return;
    }

}
void drop_to_bottom(void) {
    while (!is_collision(current_block, block_state, x, y + 1)) {
        y++;
    }
    fix_block(current_block, block_state, x, y);
    clear_lines = clear_full_line();
    point += point_for_line(clear_lines);
    spawn_new_block();
}