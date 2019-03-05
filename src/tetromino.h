#ifndef _TETROMINO_H
#define _TETROMINO_H

#include <stdbool.h>

int Tetromino_Rotate(int px, int py, int r);
bool Tetromino_Fit(unsigned char *board, unsigned char *tetromino, int rotation, int n_pos_x, int n_pos_y);
unsigned char *Tetromino_Draws(void);

#endif // _TETROMINO_H