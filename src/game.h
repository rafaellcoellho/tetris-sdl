#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>

#define SCREEN_WIDTH   14 * 20
#define SCREEN_HEIGHT  20 * 20

void Game_Create(void);
void Game_Loop(void);
void Game_Destroy(void);

#endif // _GAME_H