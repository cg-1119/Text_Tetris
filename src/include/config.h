#ifndef CONFIG_H
#define CONFIG_H

#include "type.h"

/*  
* 공통으로 쓰이는 매크로, 전역 변수 들의 모음
*/
// ----------------------------------------------------------
// 매크로

// 왼쪽, 오른쪽, 아래, 회전
#define LEFT   0
#define RIGHT  1
#define DOWN   2
#define ROTATE 3

// 게임 시작, 게임 종료
#define GAME_START 0
#define GAME_END   1

// 보드 크기
#define BOARD_ROWS 21
#define BOARD_COLS 10

// 테트로미노 개수
#define TETROMINO_COUNT 7

// ----------------------------------------------------------
// 전역 변수

extern char tetris_table[BOARD_ROWS][BOARD_COLS]; // 테이블
extern char (*tetrominos[TETROMINO_COUNT])[4][4]; // 테트로미노 집합

extern TetrominoType block_number;       // 블록 번호
extern TetrominoType next_block_number;  // 다음 블록 번호
extern int block_state;        // 블록 상태

// 블록 위치
extern int x;
extern int y;

// 게임 상태 (GAME_START, GAME_END)
extern int game;

// 점수
extern int best_point;
extern long point;

extern int clear_lines; // 클리어된 라인 수

#endif // CONFIG_H