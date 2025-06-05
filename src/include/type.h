#ifndef TYPE_H
#define TYPE_H

/**
 * 구조체들의 집합
 */

typedef enum {
    BLOCK_I,
    BLOCK_O,
    BLOCK_T,
    BLOCK_S,
    BLOCK_Z,
    BLOCK_J,
    BLOCK_L
} Tetromino;

// 게임 결과 저장용 구조체
typedef struct {
    char  name[30];
    long  point;
    int   year;
    int   month;
    int   day;
    int   hour;
    int   min;
    int   rank;
} Result;

#endif // TYPE_H