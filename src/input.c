#include "include/input.h"

#ifdef _WIN32

  #include <conio.h>
  #include <windows.h>
  #include <stdio.h>

  void setup_terminal(void) {
    printf("\x1b[?25l");
    setvbuf(stdout, buf, _IOFBF, 1000);
  }
  void restore_terminal(void) {
    printf("\x1b[?25h");
    fflush(stdout);
    setvbuf(stdout, NULL, _IONBF, 0);
  }
  int get_key(void) {
      if (_kbhit()) {
          return _getch();
      }
      return 0;
  }
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    // 이전 터미널 설정을 저장할 변수
    static struct termios old_tio, new_tio;
    static char buf[1000];

    void setup_terminal(void) {
        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio; // 원래 설정 old_tio에 저장

        // 논블로킹, 노에코 모드 전환
        new_tio.c_lflag &= ~(ICANON | ECHO);
        new_tio.c_cc[VMIN]  = 0;
        new_tio.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        printf("\x1b[?25l"); // ANSI 이스케이프 코드로 커서 숨기기
        setvbuf(stdout, buf, _IOFBF, 1000);
    }
    void restore_terminal(void) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); // 원래 설정으로 복원
        printf("\x1b[?25h"); // ANSI Escape 코드로 커서 보이게 수정
        fflush(stdout);
        setvbuf(stdout, NULL, _IONBF, 0);
    }

    int get_key(void) {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            return (int)ch;
        }
        return 0;
    }
#endif