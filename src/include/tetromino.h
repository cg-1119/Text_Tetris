#ifndef TETROMINO_H
#define TETROMINO_H

/**
 * 블록 관련된 로직들을 담당합니다. (생성, 움직임)
 */

void init_tetromino(void);
void spawn_new_block(void);

void move_left(void);
void move_right(void);
void move_down(void);
void rotate_block(void);
void drop_to_bottom(void);

#endif // TETROMINO_H