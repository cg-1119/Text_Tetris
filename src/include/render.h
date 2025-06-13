#ifndef RENDER_H
#define RENDER_H

#include <stddef.h>

/**
 * 유저 반응을 위한 화면 출력을 담당
 */

// 메뉴
void draw_main_menu(void);

// 화면 갱신용 버퍼링
void ui_init_screen_buffer(void);
void build_frame_buffer(void);
void diff_and_draw(void);
void ui_restore_screen(void);

// 게임 오버·예외
void draw_game_over(void);
void draw_savefile_exception_message(void);

// 기록·검색
void draw_record_page(int page_index);
void draw_search_page(void);
void draw_search_results(char *query);

#endif // RENDER_H
