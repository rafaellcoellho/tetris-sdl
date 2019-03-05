#ifndef _INPUT_H
#define _INPUT_H

#include <stdbool.h>

#define MAX_KEYBOARD_KEYS 350

void read_input(bool *exit_game);
bool left_arrow_key(void);
bool right_arrow_key(void);
bool down_arrow_key(void);
bool space_key(void);
bool esc_key(void);

#endif // _GAME_H