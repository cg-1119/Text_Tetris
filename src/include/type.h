#ifndef TYPE_H
#define TYPE_H

/**
 * 구조체들의 집합
 */

 // 테트리스 번호들을 enum으로 선언
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

// 게임 결과 저장의 자료구조를 linked list로 설정
typedef struct Node_{
    Result data;
    struct Node_ *next;
} Node;

// head부분을 ResultList로 명명
typedef Node* ResultList;

typedef enum {
    SAVE_FILE_EXCEPTION
} ExceptionCode;

#endif // TYPE_H