#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "game.h"
#include "input.h"
#include "board.h"
#include "tetromino.h"

static bool exit_game = false;
static bool game_over = false;
static SDL_Renderer *renderer;
static SDL_Window *window;
static unsigned char *p_board;

unsigned char *current_tetromino;
int current_rotation = 0;
int current_x = BOARD_WIDTH / 2;
int current_y = 0;

bool can_force_down = false;
int game_speed = 20;

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

static void prepare_scene(void)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

static void present_scene(void)
{
	SDL_RenderPresent(renderer);
}

static void move_tetromino(void)
{
	static int filter = 5;
	static bool space_hold = false;

	if(filter == 0) {
		if (left_arrow_key()) {
			if(Tetromino_Fit(p_board, current_tetromino, current_rotation, current_x-1, current_y)) current_x -= 1;
		}

		if (right_arrow_key()) {
			if(Tetromino_Fit(p_board, current_tetromino, current_rotation, current_x+1, current_y)) current_x += 1;
		}

		if (down_arrow_key()) {
			if(Tetromino_Fit(p_board, current_tetromino, current_rotation, current_x, current_y+1)) current_y += 1;
		}

		if (space_key()) {
			if(!space_hold && Tetromino_Fit(p_board, current_tetromino, current_rotation+1, current_x, current_y)) current_rotation += 1;
			space_hold = true;
		} else space_hold = false;

		filter = 5;
	}
	filter--;
}

static void force_down(void)
{
	static int speed_counter = 0;

	speed_counter++;
	can_force_down = (speed_counter == game_speed);

	if(can_force_down) {
		if(Tetromino_Fit(p_board, current_tetromino, current_rotation, current_x, current_y+1)) current_y++;
		else {

			Tetromuni_Lock(p_board, current_tetromino, current_rotation, current_x, current_y);

			for(int py = 0; py < 4; py++) {
				if(current_y + py < BOARD_HEIGHT - 1) {
					bool line = true;
					int index_board;
					for(int px = 1; px < BOARD_WIDTH-1; px++) {
						index_board = (current_y + py) * BOARD_WIDTH + px;
						line &= (p_board[index_board]) != 0;
					}
					if(line) {
						for(int px = 1; px < BOARD_WIDTH-1; px++) {
							for(int aux = current_y+py; aux > 0; aux--) {
								p_board[aux * BOARD_WIDTH + px] = p_board[(aux - 1) * BOARD_WIDTH + px];
							}
						}
					}
				}
			}

			current_x = BOARD_WIDTH / 2;
			current_y = 0;
			current_rotation = 0;
			current_tetromino = Tetromino_Draws();

			game_over = !Tetromino_Fit(p_board, current_tetromino, current_rotation, current_x, current_y);
		}
		speed_counter = 0;
	}
}

static void logic(void)
{
	move_tetromino();
	force_down();
}

void Game_Create(void)
{
    init_sdl();

	p_board = Board_Create();

}

void Game_Loop(void)
{
    long then;
	float remainder;

    then = SDL_GetTicks();
	remainder = 0;
	current_tetromino = Tetromino_Draws();
    while(exit_game == false && game_over == false){
		prepare_scene();

        read_input(&exit_game);
		if( esc_key() ) exit_game = true;

		logic();

		Board_Render(renderer, current_tetromino, current_rotation, current_x, current_y);

		present_scene();

        cap_frame_rate(&then, &remainder);
    }
}

void Game_Destroy(void)
{
	Board_Destroy();
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}