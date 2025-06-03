#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>

void init_board(void);
bool is_collision(int type, int rotation, int row, int col);
#endif //BOARD_H
