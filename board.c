#include "board.h"
//set board size
int BOARD_WIDTH = 250;
int BOARD_HEIGHT = 500;

//set board displacement from top left corner of window
int P1_DISPLACEMENT_X = 50;
int P1_DISPLACEMENT_Y = 50;
int P2_DISPLACEMENT_X = 300;
int P2_DISPLACEMENT_Y = 50;

void drawBoard(SDL_Renderer* renderer,int player){
  SDL_Rect board;
  int displacementX,displacementY;
  int row,col;
  
  if (player == 1){
    displacementX = P1_DISPLACEMENT_X;
    displacementY = P1_DISPLACEMENT_Y;
  }else if (player == 2){
    displacementX = P2_DISPLACEMENT_X;
    displacementY = P2_DISPLACEMENT_Y;
  }
  
  board.x = displacementX;
  board.y = displacementY;
  board.w = BOARD_WIDTH;
  board.h = BOARD_HEIGHT;
      
  SDL_SetRenderDrawColor(renderer, 255, 255,255, 255 );
  SDL_RenderDrawRect(renderer,&board);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255,255,255, 15 );
      
  for(row = 1; row <= 19; row++){
    SDL_RenderDrawLine(renderer,
		       P1_DISPLACEMENT_X,
		       row*25+P1_DISPLACEMENT_Y,
		       BOARD_WIDTH+P1_DISPLACEMENT_X,
		       row*25 + P1_DISPLACEMENT_Y);
  }
  for(col = 1; col <= 10; col++){
    SDL_RenderDrawLine(renderer,
		       col*25 + P1_DISPLACEMENT_X,
		       P1_DISPLACEMENT_Y,
		       col*25 + P1_DISPLACEMENT_X,
		       BOARD_HEIGHT + P1_DISPLACEMENT_Y);
  }
  SDL_RenderPresent(renderer);
  //reset color blending
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void colorBoard(SDL_Renderer* renderer,int** board,int player){
  int i,j;
  int displacementX,displacementY;
  SDL_Rect curr;
  if (player == 1){
    displacementX = P1_DISPLACEMENT_X;
    displacementY = P1_DISPLACEMENT_Y;
  }else if (player == 2){
    displacementX = P2_DISPLACEMENT_X;
    displacementY = P2_DISPLACEMENT_Y;
  }
  
  curr.w = 23;
  curr.h = 23;
  
  for(i=0; i<10; i++){
    for(j=2; j<22; j++){
      switch(board[i][j]){
      case 0:
	SDL_SetRenderDrawColor( renderer,   0,   0,   0,   0 ); //black
	break;
      case 1:
	SDL_SetRenderDrawColor( renderer,   0, 255, 255, 255 ); //I cyan
	break;
      case 2:
	SDL_SetRenderDrawColor( renderer,   0,   0, 255, 255 ); //J blue
	break;
      case 3:
	SDL_SetRenderDrawColor( renderer, 255, 165,   0, 255 ); //L orange
	break;
      case 4:
	SDL_SetRenderDrawColor( renderer, 255, 255,   0, 255 ); //O yellow
	break;
      case 5:
	SDL_SetRenderDrawColor( renderer, 124, 252,   0, 255 ); //S lime
	break;
      case 6:
	SDL_SetRenderDrawColor( renderer, 128,   0, 128, 255 ); //T purple
	break;
      case 7:
	SDL_SetRenderDrawColor( renderer, 255,   0,   0, 255 ); //Z red
	break;
      }
      curr.x = displacementX + i * 25 + 1;
      curr.y = displacementY + (j-2) * 25 + 1;
      SDL_RenderFillRect(renderer,&curr);
    }
  }
}
