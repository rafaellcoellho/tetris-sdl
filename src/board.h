#ifndef _BOARD_H
#define _BOARD_H

#include <SDL2/SDL.h>

#define BOARD_WIDTH   14
#define BOARD_HEIGHT  20

unsigned char *Board_Create(void);
void Board_Destroy(void);
void Board_Render(SDL_Renderer *renderer, unsigned char *current_tetromino, int current_rotation, int current_x, int current_y);

#endif // _BOARD_H