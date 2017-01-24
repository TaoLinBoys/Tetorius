#include "pieces.h"

struct_piece dropDown(struct_piece Piece){
  int i;
  Piece.yorigin++;
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
