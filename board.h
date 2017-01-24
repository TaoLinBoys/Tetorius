#ifndef BOARD_H_
#define BOARD_H_
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

/*
int board(int **grid);
int printBoard(int **grid);
*/
void drawBoard(SDL_Renderer* renderer,int player);
void colorBoard(SDL_Renderer* renderer,int** board,int player);

#endif
