#include <stdlib.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "tetromino.h"

static unsigned char *field;

unsigned char *Board_Create(void)
{
    field = malloc(sizeof(unsigned char)*BOARD_WIDTH*BOARD_HEIGHT);
    
    for(unsigned int x = 0; x < BOARD_WIDTH; x++) {
        for(unsigned int y = 0; y < BOARD_HEIGHT; y++) {
            field[y*BOARD_WIDTH + x] = (x == 0 || x == BOARD_WIDTH-1 || y == BOARD_HEIGHT-1) ? 9 : 0;
        }
    }

    return field;
}

void Board_Destroy(void)
{
    free(field);
}

void Board_Render(SDL_Renderer *renderer, unsigned char *current_tetromino, int current_rotation, int current_x, int current_y)
{
    SDL_Rect block;

    block.x = 0;
    block.y = 1;
    block.w = 18;
    block.h = 18;

    for(unsigned int y = 0; y < BOARD_HEIGHT; y++) {
        for(unsigned int x = 0; x < BOARD_WIDTH; x++) {
            block.x += 1;

            if (field[y*BOARD_WIDTH + x] == 0) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    // White
            else if (field[y*BOARD_WIDTH + x] == 1) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // Red
            else if (field[y*BOARD_WIDTH + x] == 2) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
            else if (field[y*BOARD_WIDTH + x] == 3) SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Magenta
            else if (field[y*BOARD_WIDTH + x] == 4) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // Blue
            else if (field[y*BOARD_WIDTH + x] == 5) SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Cyan
            else if (field[y*BOARD_WIDTH + x] == 6) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // Green
            else if (field[y*BOARD_WIDTH + x] == 7) SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
            else if (field[y*BOARD_WIDTH + x] == 9) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     // Black
            
            SDL_RenderDrawRect(renderer, &block);
            SDL_RenderFillRect(renderer, &block);
            block.x += 19;
        }
        block.x = 0;
        block.y += 20;
    }

    block.x = 0;
    block.y = 0;

    for(int py = 0; py < 4; py++) {
        for(int px = 0; px < 4; px++) {
            int index_piece = Tetromino_Rotate(px, py, current_rotation);
            if(current_tetromino[index_piece] > 0) {
                block.x = ((current_x + px) * 20) + 1;
                block.y = ((current_y + py) * 20) + 1;

                if (current_tetromino[index_piece] == 1) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);          // Red
                else if (current_tetromino[index_piece] == 2) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);   // Yellow
                else if (current_tetromino[index_piece] == 3) SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   // Magenta
                else if (current_tetromino[index_piece] == 4) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);     // Blue
                else if (current_tetromino[index_piece] == 5) SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);   // Cyan
                else if (current_tetromino[index_piece] == 6) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);     // Green
                else if (current_tetromino[index_piece] == 7) SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);   // Orange

                SDL_RenderDrawRect(renderer, &block);
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}