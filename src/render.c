#include "include/render.h"
#include "include/config.h"
#include "include/type.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FB_ROWS    TABLE_ROWS
#define FB_COLS   ((TABLE_COLS * 2) + 30)

// 커서 제어
#define CSI_HIDE_CURSOR  "\x1b[?25l"
#define CSI_SHOW_CURSOR  "\x1b[?25h"
#define CSI_CLEAR_SCREEN "\x1b[2J"
#define CURSOR_POS(r,c)  printf("\x1b[%d;%dH", (r), (c))

// 프레임 버퍼
static char old_frame[FB_ROWS][FB_COLS];
static char new_frame[FB_ROWS][FB_COLS];

// 프레임 버퍼에 출력할 텍스트를 저장하는 인라인 함수들
// -----------------------------------------------------------
static inline void build_table(void) {
    for (int row = 0; row < TABLE_ROWS - 1; row++) {
        for (int col = 0; col < TABLE_COLS; col++) {
            int frame_col = col * 2;
            if (tetris_table[row][col]) {
                new_frame[row][frame_col]     = '[';
                new_frame[row][frame_col + 1] = ']';
            } else {
                new_frame[row][frame_col]     = ' ';
                new_frame[row][frame_col + 1] = ' ';
            }
        }
    }
    // 바닥
    int last_row = TABLE_ROWS - 1;
    for (int col = 0; col < TABLE_COLS; col++) {
        int frame_col = col * 2;
        new_frame[last_row][frame_col]     = '[';
        new_frame[last_row][frame_col + 1] = ']';
    }
}

static inline void build_tetromino(void) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[block_number][block_state][row][col]) {
                int frame_row = y + row;
                int frame_col = (x + col) * 2;
                new_frame[frame_row][frame_col]     = '[';
                new_frame[frame_row][frame_col + 1] = ']';
            }
        }
    }
}

static inline void build_point(void) {
    char buf1[32], buf2[32];
    int len1 = snprintf(buf1, sizeof(buf1), "Best Point : %d", best_point);
    int len2 = snprintf(buf2, sizeof(buf2), "Point      : %ld", point);

    int start_col = (TABLE_COLS * 2) + 1; 

    for (int i = 0; i < len1; i++) {
        new_frame[0][start_col + i] = buf1[i];
    }
    for (int i = 0; i < len2; i++) {
        new_frame[1][start_col + i] = buf2[i];
    }
}

static inline void build_next_block(void) {
    const int start_col = (TABLE_COLS * 2) + 1;
    const int title_row = 5;

    const char *label = "Next";
    for (int i = 0; label[i]; i++) {
        new_frame[title_row][start_col + i + 5] = label[i];
    }

    // 박스 테두리
    const char *border = "+------------+";
    int width     = (int)strlen(border);
    int top_row   = title_row + 1;
    int bottom_row= title_row + 7;
    int left_col  = start_col;

    for (int i = 0; i < width; i++) {
        new_frame[top_row][left_col + i] = border[i];
    }
    for (int r = top_row + 1; r < bottom_row; r++) {
        new_frame[r][left_col]             = '|';
        new_frame[r][left_col + width - 1] = '|';
    }
    for (int i = 0; i < width; i++) {
        new_frame[bottom_row][left_col + i] = border[i];
    }

    // 다음블록
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[next_block_number][LEFT][row][col]) {
                int frame_row = top_row + 2 + row;
                int frame_col = left_col + 5 + col * 2;
                new_frame[frame_row][frame_col]     = '[';
                new_frame[frame_row][frame_col + 1] = ']';
            }
        }
    }
}
// -----------------------------------------------------------

void ui_init_screen_buffer(void) {
    for (int row = 0; row < FB_ROWS; row++)
        for (int col= 0; col < FB_COLS; col++)
            old_frame[row][col] = ' ';
    printf(CSI_CLEAR_SCREEN CSI_HIDE_CURSOR);
}

void build_frame_buffer(void) {
    for (int row = 0; row < FB_ROWS; row++)
        for (int col = 0; col < FB_COLS; col++)
            new_frame[row][col] = ' ';

    build_table();
    build_tetromino();
    build_point();
    build_next_block();
}

void diff_and_draw(void) {
    for (int row = 0; row < FB_ROWS; row++) {
        for (int col = 0; col < FB_COLS; col++) {
            if (new_frame[row][col] != old_frame[row][col]) {
                CURSOR_POS(row + 1, col + 1);
                putchar(new_frame[row][col]);
                old_frame[row][col] = new_frame[row][col];
            }
        }
    }
}

void ui_restore_screen(void) {
    printf(CSI_SHOW_CURSOR);
}


void draw_main_menu(void) {
    printf("\x1b[2J");
    printf("\x1b[H");
    printf("\n\n\t\t\t\tText Tetris\n");
    printf("\t\t\t============================\n");
    printf("\t\t\t\tGAME MENU\n");
    printf("\t\t\t============================\n");
    printf("\t\t\t   1) Game Start\n");
    printf("\t\t\t   2) Search history\n");
    printf("\t\t\t   3) Record Output\n");
    printf("\t\t\t   4) QUIT\n");
    printf("\t\t\t============================\n");
    printf("\t\t\t\t\t SELECT : ");
}
void draw_game_over(void) {
    printf("\x1b[%d;%dH", 7, 1);
    printf("+==============================+\n");
    printf("|           Game Over          |\n");       
    printf("+==============================+\n");
    printf("|        your point: %-5ld     |\n", point);
    if (!point) {
        printf("|0 point do not support record |\n");
        printf("|Press Enter key to exit game. |\n");
    }
    else
        printf("|   Input your name:           |\n");
    printf("+==============================+");
    fflush(stdout);
}

void draw_savefile_exception_message(void) {
    printf("Unable to load save file. Please delete ‘points.txt’ and restart the application\n");
    printf("Press Enter key to exit program.");
}


void draw_record_page(int page_index) {
    printf("\x1b[2J");
    printf("\x1b[H");

    // 보여줄 페이지가 없는 경우 종료
    int total_pages = (list_length + 4) / 5;
    if (total_pages == 0) {
        printf("No search game record.\n");
        printf("Press Enter key to game menu.");
        return;
    }
    // 총 페이지 수 보여주기
    printf("==== Game Results (Page %d of %d, Total %d to %d of %d) ====\n\n",
           page_index + 1,
           total_pages,
           list_length,
           page_index * 5 + 1,
           (page_index * 5 + 5 < list_length ? page_index * 5 + 5 : list_length));

    printf("%-4s %-20s %-8s %-16s\n",
           "Rank", "Name", "Point", "Date-Time");
    printf("--------------------------------------------------------\n");

    // page_index * 5 만큼 건너뛴 뒤, 최대 5개를 출력
    Node *cur = result_list;
    int to_skip = page_index * 5;
    for (int i = 0; i < to_skip && cur; i++) {
        cur = cur->next;
    }

    int printed = 0;
    while (cur && printed < 5) {
        Result *r = &cur->data;
        printf("%-4d %-20s %-8ld %04d-%02d-%02d %02d:%02d\n",
               r->rank,
               r->name,
               r->point,
               r->year, r->month, r->day,
               r->hour, r->min);
        printed++;
        cur = cur->next;
    }

    if (printed == 0) {
        printf("\t[No results to display on this page]\n");
    }

    printf("\n[j] Previous Page    [l] Next Page    [p] Quit\n");
    fflush(stdout);
}

void draw_search_page(void) {
    printf("\x1b[2J");
    printf("\x1b[%d;%dH", 6, 22);
    printf("+==============================+\n");
    printf("\x1b[%d;%dH", 7, 22);
    printf("|          Search Page         |\n");
    printf("\x1b[%d;%dH", 8, 22);
    printf("+==============================+\n");
    printf("\x1b[%d;%dH", 9, 22);
    printf("|   name:                      |\n");
    printf("\x1b[%d;%dH", 10, 22);
    printf("+==============================+");
}

void draw_search_results(char *query) {
    printf("\x1b[2J");
    printf("\x1b[H");
    printf("============ Search Results for \"%s\" ============\n\n", query);
    printf("%-4s %-20s %-8s %-16s\n",
           "Rank", "Name", "Point", "Date-Time");
    printf("--------------------------------------------------------\n");
    
    // 리스트 순회하며 부분 일치 검색
    Node *cur = result_list;
    int found = 0;
    while (cur) {
        char name_lower[30], query_lower[30]; // 대소문자 구분 없이 일치하는지 검사
        // 원본 복사 후 소문자로 변환
        strncpy(name_lower, cur->data.name, sizeof(name_lower));
        name_lower[sizeof(name_lower)-1] = '\0';
        for (int i = 0; name_lower[i]; i++) {
            name_lower[i] = tolower((unsigned char)name_lower[i]);
        }
        strncpy(query_lower, query, sizeof(query_lower));
        query_lower[sizeof(query_lower)-1] = '\0';
        for (int i = 0; query_lower[i]; i++) {
            query_lower[i] = tolower((unsigned char)query_lower[i]);
        }

        if (strstr(name_lower, query_lower)) {
            // 일치하는 레코드가 있으면 출력
            Result *r = &cur->data;
            printf("%-4d %-20s %-8ld %04d-%02d-%02d %02d:%02d\n",
                   r->rank,
                   r->name,
                   r->point,
                   r->year, r->month, r->day,
                   r->hour, r->min);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) {
        printf("\n[No matching records found]\n");
    }

    printf("\nPress Enter to return to menu");
    fflush(stdout);
}