#ifndef PIECES_H_
#define PIECES_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct piece{
  int type;
  int x[4];
  int y[4];
  int xorigin;
  int yorigin;
} struct_piece;

int initPieces(struct_piece I_BLOCK,struct_piece J_BLOCK,
	       struct_piece L_BLOCK,struct_piece O_BLOCK,
	       struct_piece S_BLOCK,struct_piece T_BLOCK,
	       struct_piece Z_BLOCK);

int rotate(struct_piece Piece,int i);
int dropDown(struct_piece Piece);

//helpers
int shuffle(int arr[]);
int swap(int *a, int *b);
#endif
