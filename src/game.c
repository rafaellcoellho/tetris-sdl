#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "game.h"
#include "input.h"

static bool exit_game = false;
static SDL_Renderer *renderer;
static SDL_Window *window;

static void init_sdl(void) 
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	
	windowFlags = 0;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Initializing SDL");
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Create Window");
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Create Renderer");
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

static void cap_frame_rate(long *then, float *remainder)
{
	long wait, frameTime;
	
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;
	
	if (wait < 1) 
		wait = 1;
		
	SDL_Delay(wait);
	
	*remainder += 0.667;
	*then = SDL_GetTicks();
}

void Game_Create(void)
{
    init_sdl();
}

void Game_Loop(void)
{
    long then;
	float remainder;

    then = SDL_GetTicks();
	remainder = 0;
    while(exit_game == false){
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderClear(renderer);

        read_input(&exit_game);

        SDL_RenderPresent(renderer);

        cap_frame_rate(&then, &remainder);
    }
}

void Game_Destroy(void)
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}