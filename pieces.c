#include "pieces.h"

struct_piece dropDown(struct_piece Piece){
  int i;
  Piece.yorigin++;
  return Piece;  
}

int isDie(struct_piece Piece, int**grid){
  int i;
  for(i=0;i<4;i++){
    int x = Piece.x[i] + Piece.xorigin;
    int y = Piece.y[i] + Piece.yorigin;
    if(x < 0 || x > 9 || y < 0 || y > 21 || grid[x][y]) return 1;
  }
  return 0;
}
struct_piece rotate(struct_piece Piece,int i){
  //if O_BLOCK(square) don't rotate
  int j; 
  if (i>0){  //clockwise rotation
    for (j=0; j<4;j++){
      int newX = Piece.y[j];
      int newY = Piece.x[j] * (-1);
      Piece.x[j] = newX;
      Piece.y[j] = newY;
    }
  }
  if (i<0){  //counterclockwise rotation
    for (j=0; j<4;j++){
      int newX = Piece.y[j] * (-1);
      int newY = Piece.x[j];
      Piece.x[j] = newX;
      Piece.y[j] = newY;
    }
  }
  return Piece;
}
struct_piece move(struct_piece Piece,int displacement){
  Piece.xorigin+=displacement;
  return Piece;
}

//helpers
int shuffle(int arr[]) {
  srand(time(NULL));
  int i;
  for(i = 7; i > 0; i--) {
    int j = rand() % (i+1);
    swap(&arr[i], &arr[j]);
    //printf("pieces[%d] = %d",i,arr[j]);
  }
}

int swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


