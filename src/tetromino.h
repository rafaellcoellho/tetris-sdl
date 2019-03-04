#ifndef _TETROMINO_H
#define _TETROMINO_H

#include <stdbool.h>

extern unsigned char I[];
extern unsigned char J[];
extern unsigned char L[];
extern unsigned char O[];
extern unsigned char S[];
extern unsigned char T[];
extern unsigned char Z[];

int Tetromino_Rotate(int px, int py, int r);
bool Tetromino_Fit(unsigned char *board, unsigned char *tetromino, int rotation, int n_pos_x, int n_pos_y);

#endif // _TETROMINO_H