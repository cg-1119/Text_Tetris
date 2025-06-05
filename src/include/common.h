#ifndef TETRIS_COMMON_H
#define TETRIS_COMMON_H
/*
* 공통으로 쓰이는 매크로, 전역 변수 들의 모음
*/

/* 왼쪽, 오른쪽, 아래, 회전 */
#define LEFT   0
#define RIGHT  1
#define DOWN   2
#define ROTATE 3

/* 게임 시작, 게임 종료 */
#define GAME_START 0
#define GAME_END   1

extern char tetris_table[21][10];
// 블럭 집합
extern char (*all_blocks[7])[4][4];

// 게임 결과 저장용 구조체
typedef struct Result_ {
    char  name[30];
    long  point;
    int   year;
    int   month;
    int   day;
    int   hour;
    int   min;
    int   rank;
} Result;

// 전역 변수
extern int block_number;       // 블록 번호
extern int next_block_number;  // 다음 블록 번호
extern int block_state;        // 블록 상태

// 블록 위치
extern int x;
extern int y;

// 게임 상태 (GAME_START, GAME_END)
extern int game;

// 점수
extern int best_point;
extern long point;

#endif // TETRIS_COMMON_H