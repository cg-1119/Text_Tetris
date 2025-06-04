#ifndef INPUT_H
#define INPUT_H

/**
 * 터미널을 논블로킹·논에코 모드로 전환하고, 화면 출력 시 커서를 숨깁니다.
 */
void setup_terminal(void);
/**
 * 터미널 설정을 원래대로 복구하고, 커서를 다시 보이게 합니다.
 */
void restore_terminal(void);
int get_key(void);

#endif //INPUT_H
