#ifndef RENDER_H
#define RENDER_H

#include <stddef.h>

/**
 * 유저 반응을 위한 화면 출력을 담당
 */

// 메뉴
void draw_main_menu(void);

// 화면 갱신용 버퍼링

// 화면 버퍼를 초기화하고, 터미널 화면을 지우며 커서를 숨깁니다.
void ui_init_screen_buffer(void);
// 새로운 프레임 버퍼를 초기화하고, 게임 화면의 각 요소(테이블, 블록, 점수 등)를 버퍼에 그립니다.
void build_frame_buffer(void);
// 이전 프레임과 현재 프레임을 비교하여 변경된 부분만 터미널에 출력합니다.
void diff_and_draw(void);
// 커서를 다시 표시하여 터미널 화면을 원래 상태로 복원합니다.
void ui_restore_screen(void);

// 게임 오버·예외
void draw_game_over(void);
void draw_savefile_exception_message(void);

// 기록·검색
void draw_record_page(int page_index);
void draw_search_page(void);
void draw_search_results(char *query);

#endif // RENDER_H
