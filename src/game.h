#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>

#define SCREEN_WIDTH   350
#define SCREEN_HEIGHT  500

void Game_Create(void);
void Game_Loop(void);
void Game_Destroy(void);

#endif // _GAME_H