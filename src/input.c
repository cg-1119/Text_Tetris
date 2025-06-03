#include "include/input.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* 이전 터미널 설정을 저장할 변수 */
static struct termios old_tio, new_tio;

/**
 * 터미널을 논블로킹·논에코 모드로 전환하고, 화면 출력 시 커서를 숨깁니다.
 */
void setup_terminal(void) {
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio; // 원래 설정 old_tio에 저장

    // 논블로킹, 노에코 모드 전환
    new_tio.c_lflag &= ~(ICANON | ECHO);
    new_tio.c_cc[VMIN]  = 0;
    new_tio.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    printf("\x1b[?25l"); // ANSI 이스케이프 코드로 커서 숨기기
    fflush(stdout);
}

/**
 * 터미널 설정을 원래대로 복구하고, 커서를 다시 보이게 합니다.
 */
void restore_terminal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); // 원래 설정으로 복원
    printf("\x1b[?25h"); // ANSI Escape 코드로 커서 보이게 수정
    fflush(stdout);
}

int get_key(void) {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return (int)ch;
    }
    return 0;
}
