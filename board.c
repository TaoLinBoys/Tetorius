#include "board.h"
//this is our backend board
int board(int **grid){
  int i,j;
  grid=(int**) malloc(sizeof(int*)*260);
  for(i=0; i<26; i++){
    grid[i]=(int*) malloc(sizeof(int)*26);
    for(j=0; j<10; j++){
      grid[i][j]=0;
    }
  }
}

//for debugging
int printBoard(int **grid){
  int i,j;
  for(i=0; i<26; i++){
    for(j=0; j<10; j++){
      printf("%d ",grid[i][j]);
    }
    printf("\n");
  }
}
