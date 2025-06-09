#include "include/render.h"
#include "include/config.h"
#include "include/type.h"

#include <stdio.h>

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

void draw_game_screen(void) {
    // ANSI Escape로 화면 제어
    printf("\x1b[3J");
    printf("\x1b[2J");
    printf("\x1b[H");

    draw_table();
    draw_tetromino();
    draw_point();
    draw_next_block();
    
    fflush(stdout);
}
void draw_table(void) {
    for (int row = 0; row < TABLE_ROWS - 1; row++) {
        printf("\x1b[%d;1H", row + 1);
        for (int col = 0; col < TABLE_COLS; col++) {
            if (tetris_table[row][col]) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
        printf("\x1b[21;1H");
        for (int col = 0; col < 10; col++) {
            printf("[]");
        }
    }
}
void draw_tetromino(void) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[block_number][block_state][row][col]) {
                int table_row = y + row;
                int table_col = x + col;
                printf("\x1b[%d;%dH", table_row + 1, table_col * 2 + 1);
                printf("[]");
            }
        }
    }
}
void draw_point(void) {
    printf("\x1b[%d;%dH", 1, 22);
    printf("Best Point : %d", best_point);
    printf("\x1b[%d;%dH", 2, 22);
    printf("Point : %ld", point);
}

void draw_next_block(void) {
    printf("\x1b[%d;%dH", 5, 27);
    printf("Next");
    printf("\x1b[%d;%dH", 6, 22);
    printf("+------------+");
    for (int r = 7; r <= 11; r++) {
        printf("\x1b[%d;%dH", r, 22);
        printf("|            |");
    }
    printf("\x1b[%d;%dH", 12, 22);
    printf("+------------+");

    int next_type = next_block_number;
    // 블록 출력
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetrominos[next_type][LEFT][row][col]) {
                int table_row = 8 + row;
                int table_col = 27 + col * 2;
                printf("\x1b[%d;%dH", table_row, table_col);
                printf("[]");
            }
        }
    }
}

void draw_game_over(void) {
    printf("\x1b[%d;%dH", 7, 1);
    printf("+==============================+\n");
    printf("|           Game Over          |\n");       
    printf("+==============================+\n");
    printf("|        your point: %-5ld     |\n", point);
    if (!point) {
        printf("|0 points do not support record|\n");
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
    int seq_num = page_index * 5 + 1;
    while (cur && printed < 5) {
        Result *r = &cur->data;
        printf("%-4d %-20s %-8ld %04d-%02d-%02d %02d:%02d\n",
               seq_num,
               r->name,
               r->point,
               r->year, r->month, r->day,
               r->hour, r->min);
        printed++;
        seq_num++;
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
    printf("|          Search Page         |\n");       
    printf("+==============================+\n");
    printf("|   name:                      |\n");
    printf("+==============================+");
}