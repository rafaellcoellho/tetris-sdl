#ifndef _GAME_H
#define _GAME_H

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH   350
#define SCREEN_HEIGHT  500

#define MAX_KEYBOARD_KEYS 350

void Game_Create(void);
void Game_Loop(void);
void Game_Destroy(void);

#endif // _GAME_H