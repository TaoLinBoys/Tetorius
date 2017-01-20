#include "pieces.h"

int initPieces(struct_piece I_BLOCK,struct_piece J_BLOCK,
	       struct_piece L_BLOCK,struct_piece O_BLOCK,
	       struct_piece S_BLOCK,struct_piece T_BLOCK,
	       struct_piece Z_BLOCK){
  //struct_piece I_BLOCK;
  I_BLOCK.rotation = 0;
  I_BLOCK.xorigin = 5;
  I_BLOCK.yorigin = 2;
  I_BLOCK.x[0] = -1;
  I_BLOCK.y[0] = 0;
  I_BLOCK.x[1] = 0;
  I_BLOCK.y[1] = 0;
  I_BLOCK.x[2] = 1;
  I_BLOCK.y[2] = 0;
  I_BLOCK.x[3] = 2;
  I_BLOCK.y[3] = 0;
  //struct_piece J_BLOCK;
  J_BLOCK.rotation = 0;
  J_BLOCK.xorigin = 5;
  J_BLOCK.yorigin = 2;
  J_BLOCK.x[0] = -1;
  J_BLOCK.y[0] = 0;
  J_BLOCK.x[1] = 0;
  J_BLOCK.y[1] = 0;
  J_BLOCK.x[2] = 1;
  J_BLOCK.y[2] = 0;
  J_BLOCK.x[3] = 2;
  J_BLOCK.y[3] = 0;
  //struct_piece L_BLOCK;
  L_BLOCK.rotation = 0;
  L_BLOCK.xorigin = 5;
  L_BLOCK.yorigin = 2;
  L_BLOCK.x[0] = -1;
  L_BLOCK.y[0] = 0;
  L_BLOCK.x[1] = 0;
  L_BLOCK.y[1] = 0;
  L_BLOCK.x[2] = 1;
  L_BLOCK.y[2] = 0;
  L_BLOCK.x[3] = 2;
  L_BLOCK.y[3] = 0;
  //struct_piece O_BLOCK;
  O_BLOCK.rotation = 0;
  O_BLOCK.xorigin = 5;
  O_BLOCK.yorigin = 2;
  O_BLOCK.x[0] = 0;
  O_BLOCK.y[0] = 0;
  O_BLOCK.x[1] = 1;
  O_BLOCK.y[1] = 0;
  O_BLOCK.x[2] = 0;
  O_BLOCK.y[2] = 1;
  O_BLOCK.x[3] = 1;
  O_BLOCK.y[3] = 1;
  //struct_piece S_BLOCK;
  S_BLOCK.rotation = 0;
  S_BLOCK.xorigin = 5;
  S_BLOCK.yorigin = 2;
  S_BLOCK.x[0] = 0;
  S_BLOCK.y[0] = 0;
  S_BLOCK.x[1] = 1;
  S_BLOCK.y[1] = 0;
  S_BLOCK.x[2] = 0;
  S_BLOCK.y[2] = 1;
  S_BLOCK.x[3] = 1;
  S_BLOCK.y[3] = 1;
  //struct_piece T_BLOCK;
  T_BLOCK.rotation = 0;
  T_BLOCK.xorigin = 5;
  T_BLOCK.yorigin = 2;
  T_BLOCK.x[0] = -1;
  T_BLOCK.y[0] = 0;
  T_BLOCK.x[1] = 0;
  T_BLOCK.y[1] = 0;
  T_BLOCK.x[2] = 1;
  T_BLOCK.y[2] = 0;
  T_BLOCK.x[3] = 0;
  T_BLOCK.y[3] = 1;
  //struct_piece Z_BLOCK;
  Z_BLOCK.rotation = 0;
  Z_BLOCK.xorigin = 5;
  Z_BLOCK.yorigin = 2;
  Z_BLOCK.x[0] = -1;
  Z_BLOCK.y[0] = 0;
  Z_BLOCK.x[1] = 0;
  Z_BLOCK.y[1] = 0;
  Z_BLOCK.x[2] = 1;
  Z_BLOCK.y[2] = 0;
  Z_BLOCK.x[3] = 2;
}

int rotate(struct_piece Piece,int i){
  int newRotation = (Piece.rotation + i) % 4;
    if (newRotation < 0) {
      newRotation = 3;
    }
  
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
  return 1;
}
