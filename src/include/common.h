    #ifndef TETRIS_COMMON_H
    #define TETRIS_COMMON_H
    /*
    * 공통으로 쓰이는 매크로, 전역 변수 들의 모음
    */
    /* 타이머 */
    #define CCHAR 0
    #ifdef CTIME
    #undef CTIME
    #endif
    #define CTIME 1

    /* 왼쪽, 오른쪽, 아래, 회전 */
    #define LEFT   0
    #define RIGHT  1
    #define DOWN   2
    #define ROTATE 3

    /* 블록 모양 */
    #define I_BLOCK 0
    #define T_BLOCK 1
    #define S_BLOCK 2
    #define Z_BLOCK 3
    #define L_BLOCK 4
    #define J_BLOCK 5
    #define O_BLOCK 6

    /* 게임 시작, 게임 종료 */
    #define GAME_START 0
    #define GAME_END   1

    extern char tetris_table[21][10];
    // 블럭 집합
    extern char (*all_blocks[7])[4][4];

    // 게임 결과 저장용 구조체
    struct result {
        char  name[30];
        long  point;
        int   year;
        int   month;
        int   day;
        int   hour;
        int   min;
        int   rank;
    };
    /* 'temp_result'는 static으로 원본에서는 선언되었으나,
    파일 I/O 처리 시에는 소스 내부에서만 쓰이므로
    .c 파일 쪽에서 static으로 두면 되고, 헤더에서는 선언하지 않습니다. */

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