#include "tetromino.h"
#include "board.h"

unsigned char I[] = {0,0,1,0,
                    0,0,1,0,
                    0,0,1,0,
                    0,0,1,0};

unsigned char J[] = {0,0,2,0,
                    0,0,2,0,
                    0,2,2,0,
                    0,0,0,0};

unsigned char L[] = {0,0,3,0,
                    0,0,3,0,
                    0,0,3,3,
                    0,0,0,0};

unsigned char O[] = {0,4,4,0,
                    0,4,4,0,
                    0,0,0,0,
                    0,0,0,0};

unsigned char S[] = {0,0,5,5,
                    0,5,5,0,
                    0,0,0,0,
                    0,0,0,0};

unsigned char T[] = {0,6,6,6,
                    0,0,6,0,
                    0,0,0,0,
                    0,0,0,0};

unsigned char Z[] = {0,7,7,0,
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
