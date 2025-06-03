#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

void init_tetromino(void);
void spawn_new_block(void);

void move_left(void);
void move_right(void);
void move_down(void);
void rotate_block(void);
void drop_to_bottom(void);

#endif // TETRIS_TETROMINO_H