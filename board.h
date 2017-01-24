#ifndef BOARD_H_
#define BOARD_H_
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "pieces.h"

/*
int board(int **grid);
int printBoard(int **grid);
*/
void drawBoard(SDL_Renderer* renderer,int player);
void colorBoard(SDL_Renderer* renderer,int** board,int player);
void colorHold(SDL_Renderer* renderer,struct_piece Piece);

#endif
