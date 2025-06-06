#ifndef RENDER_H
#define RENDER_H

/**
 * 유저 반응을 위한 화면 출력을 담당
 */

void draw_main_menu(void);

// 게임 화면 출력에 필요한 요소들을 관리하는 함수
void draw_game_screen(void);
void draw_board(void);
void draw_tetromino(void);
void draw_point(void);
void draw_next_block(void);

void draw_game_over(void);

// 예기치 않은 오류가 발생하면 출력
void draw_savefile_exception_message(void);

#endif // RENDER_H