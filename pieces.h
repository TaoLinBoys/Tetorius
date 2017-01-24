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

struct_piece rotate(struct_piece Piece,int i);
struct_piece dropDown(struct_piece Piece);

//helpers
int shuffle(int arr[]);
int swap(int *a, int *b);
#endif
