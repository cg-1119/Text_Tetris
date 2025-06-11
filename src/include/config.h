#ifndef CONFIG_H
#define CONFIG_H

#include "type.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

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

// 테이블 크기
#define TABLE_ROWS 21
#define TABLE_COLS 10

// 테트로미노 개수
#define TETROMINO_COUNT 7

// ----------------------------------------------------------
// 전역 변수

extern char tetris_table[TABLE_ROWS][TABLE_COLS]; // 테이블
extern char (*tetrominos[TETROMINO_COUNT])[4][4]; // 테트로미노 집합

// block_number와 next_block_number의 자료형을 Tetromino로 변경하였습니다.

extern Tetromino block_number; // 블록 번호
extern Tetromino next_block_number;  // 다음 블록 번호
extern int block_state; // 블록 상태

// 블록 위치
extern int x;
extern int y;

// 게임 상태 (GAME_START, GAME_END)
extern int game;

// 점수
extern int best_point;
extern long point;

extern int clear_lines; // 클리어된 라인 수

extern char *filename; // 파일 이름

// 포인트 정보들을 위한 list
extern ResultList result_list;
extern int list_length; // 리스트 길이

// --------------------------------------------
// ResultList를 위한 기능
// 노드 생성
Node* make_node(Result *result);
// result_list 메모리 free
void free_list();
// --------------------------------------------

#endif // CONFIG_H