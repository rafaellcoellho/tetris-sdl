#include <time.h> 
#include <stdlib.h>
#include "tetromino.h"
#include "board.h"

static unsigned char I[] = {0,0,1,0,
                            0,0,1,0,
                            0,0,1,0,
                            0,0,1,0};

static unsigned char J[] = {0,0,2,0,
                            0,0,2,0,
                            0,2,2,0,
                            0,0,0,0};

static unsigned char L[] = {0,0,3,0,
                            0,0,3,0,
                            0,0,3,3,
                            0,0,0,0};

static unsigned char O[] = {0,4,4,0,
                            0,4,4,0,
                            0,0,0,0,
                            0,0,0,0};

static unsigned char S[] = {0,0,5,5,
                            0,5,5,0,
                            0,0,0,0,
                            0,0,0,0};

static unsigned char T[] = {0,6,6,6,
                            0,0,6,0,
                            0,0,0,0,
                            0,0,0,0};

static unsigned char Z[] = {0,7,7,0,
                            0,0,7,7,
                            0,0,0,0,
                            0,0,0,0};

int Tetromino_Rotate(int px, int py, int rotation)
{
    switch(rotation % 4) {
        case 0: return py * 4 + px;             // 0 degrees
        case 1: return 12 + py - (px * 4);      // 90 degrees
        case 2: return 15 - (py * 4) - px;      // 180 degrees
        case 3: return 3 - py + (px * 4);       // 270 degrees
    }
    return 0;
}

bool Tetromino_Fit(unsigned char *board, unsigned char *tetromino, int rotation, int n_pos_x, int n_pos_y)
{
    for(int px = 0; px < 4; px++) {
        for(int py = 0; py < 4; py++) {
            int index_piece = Tetromino_Rotate(px, py, rotation);
            int index_board = (n_pos_y + py) * BOARD_WIDTH + (n_pos_x + px);

            if(n_pos_x + px >= 0 && n_pos_x + px < BOARD_WIDTH) {
                if(n_pos_y + py >= 0 && n_pos_y + py < BOARD_HEIGHT) {
                    if (tetromino[index_piece] > 0 && board[index_board] != 0)
                        return false;
                }
            }
        }
    }
    return true;
}

unsigned char *Tetromino_Draws(void)
{
    time_t t;
    srand((unsigned) time(&t));
    int roulette = rand() % 7;

    switch(roulette) {
        case 0: return I;
        case 1: return J;
        case 2: return L;
        case 3: return O;
        case 4: return S;
        case 5: return T;
        case 6: return Z;
    }
    return 0;
}

void Tetromuni_Lock(unsigned char *board, unsigned char *tetromino, int rotation, int n_pos_x, int n_pos_y)
{
    for(int py = 0; py < 4; py++) {
        for(int px = 0; px < 4; px++) {
            int index_piece = Tetromino_Rotate(px, py, rotation);
            int index_board = (n_pos_y + py) * BOARD_WIDTH + (n_pos_x + px);
            if(tetromino[index_piece] > 0) {
                board[index_board] = tetromino[index_piece];
            }
        }
    }
}