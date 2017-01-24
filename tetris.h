#ifndef TETRIS_H_
#define TETRIS_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

//board
int board();
int removeFromBoard();
int updateBoard();
int printBoard();

//pieces
int initCurrPiece();
int nextPiece();
int hold();
int collidesAt();
int try(int action);

//rows
int clearRows();
int deleteRow(int row);

//main
int main( int argc, char* args[] );
#endif
