#ifndef LOGIC_H
#define LOGIC_H

/*
 * 메뉴, 게임 시작, 종료 등 게임의 큰 틀의 로직들의 모음
 */

int display_menu();
int game_start();
void search_result();
void print_result();

static void sleep_ms(int ms);
static void get_time_of_day(struct timeval *tv);

#endif // LOGIC_H