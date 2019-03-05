#include <SDL2/SDL.h>
#include "input.h"

static int keyboard[MAX_KEYBOARD_KEYS];

void key_up(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
		keyboard[event->keysym.scancode] = 0;
}

void key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
		keyboard[event->keysym.scancode] = 1;
}

void read_input(bool *exit_game)
{
	SDL_Event event;
	
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				*exit_game = true;
				break;
			case SDL_KEYDOWN:
				key_down(&event.key);
				break;
			case SDL_KEYUP:
				key_up(&event.key);
				break;
			default:
				break;
		}
	}
}

bool left_arrow_key(void) 
{
	return keyboard[SDL_SCANCODE_LEFT];
}

bool right_arrow_key(void) 
{
	return keyboard[SDL_SCANCODE_RIGHT];
}

bool down_arrow_key(void) 
{
	return keyboard[SDL_SCANCODE_DOWN];
}

bool space_key(void) 
{
	return keyboard[SDL_SCANCODE_SPACE];
}

bool esc_key(void)
{
	return keyboard[SDL_SCANCODE_ESCAPE];
}