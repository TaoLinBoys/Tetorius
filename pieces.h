#ifndef PIECES_H_
#define PIECES_H_

typedef struct piece{
  int rotation;
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


#endif
