#ifndef BOARD_H
#define BOARD_H

#include "type.h"
#include <stdbool.h>
/**
 * 보드에서 일어나는 관련 로직을 담당합니다.
 */

void init_board(void);
bool is_collision(Tetromino type, int rotation, int x, int y);
void fix_block(Tetromino type, int rotation, int x, int y);
/// @brief 보드를 순회하면서 다 찬 라인이 있으면 클리어합니다.
/// @return 클리어 된 라인의 수
int clear_full_line(void);
#endif //BOARD_H
