#ifndef _BOARD_H
#define _BOARD_H

#include <SDL2/SDL.h>

#define BOARD_WIDTH   12
#define BOARD_HEIGHT  18

unsigned char *Board_Create(void);
void Board_Destroy(void);
void Board_Render(SDL_Renderer *renderer);

#endif // _BOARD_H