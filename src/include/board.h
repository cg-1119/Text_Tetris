#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>

void init_board(void);
bool is_collision(int type, int rotation, int x, int y);
void fix_block(int type, int rotation, int x, int y);
void clear_full_line(int x, int y);
#endif //BOARD_H
