#include "pieces.h"
#include "board.h"

#define SDL_MAIN_HANDLED

//initial grid
int **grid;

//set window size
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


//pieces
struct_piece I_BLOCK;
struct_piece J_BLOCK;
struct_piece L_BLOCK;
struct_piece O_BLOCK;
struct_piece S_BLOCK;
struct_piece T_BLOCK;
struct_piece Z_BLOCK;

int curr;
struct_piece currPiece;
struct_piece testPiece; //testing for collisions

int pieceQueue[7];

//this is our backend board
int board(){
  int i,j;
  grid=(int**) malloc(sizeof(int*)*220);
  for(i=0; i<22; i++){
    grid[i]=(int*) malloc(sizeof(int)*22);
    for(j=0; j<10; j++){
      grid[i][j]=0;
    }
  }
}

//for debugging
int printBoard(){
  int i,j;
  for(i = 0; i<22; i++){
    for(j=0; j<10; j++){
      printf("%d ",grid[i][j]);
    }
    printf("\n");
  }
}

int initCurrPiece(){
  int i;
  for(i=0;i<7;i++) pieceQueue[i] = i;
  shuffle(pieceQueue);
  curr = 0;
  switch (pieceQueue[curr]){
  case 0: currPiece = I_BLOCK;
  case 1: currPiece = J_BLOCK;
  case 2: currPiece = L_BLOCK;
  case 3: currPiece = O_BLOCK;
  case 4: currPiece = S_BLOCK;
  case 5: currPiece = T_BLOCK;
  case 6: currPiece = Z_BLOCK;
  }
}
   
int nextPiece(){
  if (curr=7){  
    shuffle(pieceQueue); //execute when you have gotten all 7 pieces
    curr = 0;
  }
  curr++;
  printf("curr= %d\n",curr);
}

int collidesAt(struct_piece Piece){
  int i;
  for(i=0;i<4;i++){
    int x = Piece.x[i] + Piece.xorigin;
    int y = Piece.y[i] + Piece.yorigin;
    if(grid[x][y]) return 1;
  }
  //printf("--doesn't collide\n");
  return 0;
}


int isLowest(struct_piece Piece){
  if (dropDown(testPiece)){
    if (collidesAt(testPiece)){return 1;}//does collides when testpiece is dropped
    else{return 0;}      //test piece can drop without colliding
  }
  else{return 1;}            //cant drop down bc at bottom of board
}

int move(struct_piece Piece,int displacement){
  int i;
  int x;
  for (i=0;i<4;i++){
    x = Piece.x[i] + Piece.xorigin;
    if (x+displacement<0 || x+displacement>10) return 0;
  }
  Piece.xorigin+=displacement;
  return 1;
}

/*
  int updateBoard(){ //doesn't work properly
  int i;
  for (i=0;i<4;i++){
  int x=testPiece.xorigin + testPiece.x[i];
  int y=testPiece.yorigin + testPiece.y[i];
  grid[x][y]=1;
  }
  }
*/
int resetTestPiece(){
  testPiece.rotation = currPiece.rotation;
  testPiece.xorigin = currPiece.xorigin;
  testPiece.yorigin = currPiece.yorigin;
  int i;
  for(i=0;i<4;i++){
    testPiece.x[i] = currPiece.x[i];
    testPiece.y[i] = currPiece.y[i];  
  }
  //printf("reseted test piece\n");
  return 1;
}

//return 0 -> can't make move || return 1 -> possible move
int try(int action){ //{0:+rotate,1:-rotate,2:leftmove,3:rightmove,4:down}
  int valid;
  switch(action){
  case 0:
    printf("up pressed\n");
    rotate(testPiece,1);
    valid = !(collidesAt(testPiece));
    resetTestPiece();
    if (valid)return 1;
    else{return 0;}
 
  case 1:
    printf("rctrl pressed\n");
    rotate(testPiece,-1);
    valid = !(collidesAt(testPiece));
    resetTestPiece();
    if (valid) {
      return 1;
      printf("asdas");}
    else{return 0;}
  
  case 2:
    printf("left pressed\n");
    move(testPiece,-1);
    int valid = !(collidesAt(testPiece));
    resetTestPiece();
    if (valid) return 1;
    else{return 0;}

  case 3:
    printf("right pressed\n");
    move(testPiece,1);
    valid = !(collidesAt(testPiece));
    resetTestPiece();
    if (valid) return 1;
    else{return 0;}

  case 4:
    printf("down pressed\n");
    dropDown(testPiece);
    valid = !(collidesAt(testPiece));
    resetTestPiece();
    if (valid) return 1;
    else{return 0;}   
  }

}

int isDie(){
  return collidesAt(currPiece);
}




/*
//this is prob wrong. i'll fix later
int deleteRow(int row){
for (int j = row-1; j > 0; j--) {
for (int i = 1; i < 11; i++) {
board[i-1][j+2] = board[i-1][j+1];
}
}
return 1;
}
 
SDL_MOUSEBUTTONUP

//TIMERS: https://wiki.libsdl.org/SDL_AddTimer?highlight=%28%5CbCategoryTimer%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruc%29
Uint32 delay = (level*1.2) * 1000
SDL_TimerID gravity_id = SDL_AddTimer(Uint32            interval,
SDL_TimerCallback callback,
void*             param)
*/


int main( int argc, char* args[] )
{
  
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  SDL_Renderer* renderer = NULL;
  if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } 
  else{
    window = SDL_CreateWindow("Tetris",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      SCREEN_WIDTH,
			      SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	       
    if( window == NULL ){
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else{
      //INITIALIZING BOARD AND PIECES (backend)
      board();
      printf("board initialized\n");
      initPieces(I_BLOCK,J_BLOCK,L_BLOCK,O_BLOCK,S_BLOCK,T_BLOCK,Z_BLOCK);
      initCurrPiece();
      printf("curr = %d, pieceQueue[curr] = %d\n",curr,pieceQueue[curr]);
      //updateBoard();
      printBoard();

      drawBoard(renderer,1);

      //reset color blending
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

      colorBoard(renderer,grid,1);
      int close_requested = 0;

      while(!close_requested){
	//process events
	SDL_Event event;
	while (SDL_PollEvent(&event)){

	  switch(event.type){
	  case SDL_QUIT:
	    close_requested = 1;
	    break;
	  case SDL_KEYDOWN:
	    switch(event.key.keysym.scancode){
	    case SDL_SCANCODE_UP:
	      if (try(0))rotate(currPiece,1);
	    case SDL_SCANCODE_RCTRL:
	      if (try(1)) rotate(currPiece,-1);
	    case SDL_SCANCODE_LEFT:
	      if (try(2)) move(currPiece,-1);
	    case SDL_SCANCODE_RIGHT:
	      if (try(3)) move(currPiece,1);
	    case SDL_SCANCODE_DOWN:
	      if (try(4)) dropDown(currPiece);
	    }
	    //updateBoard();
	    //printBoard();
	  }
	}
	/*
	  if (event.type ==SDL_QUIT){  
	  close_requested = 1;       
	  SDL_DestroyWindow( window );
	  SDL_Quit();
	  break;
	  }
	  }
	*/
	/*
	  int i,j;
	  SDL_Rect currentRect = {.w = 25,.h=25};
	  for(i=0; i<26; i++){
	  for(j=0; j<10; j++){
	  currentRect.x = P1_DISPLACEMENT_Y + i*25;
	  currentRect.y = P1_DISPLACEMENT_X + j*25;
	  if (grid[j][i]){
	  SDL_SetRenderDrawColor(renderer,255,0,0,0);
	  }
	  else{
	  SDL_SetRenderDrawColor(renderer,0,0,0,0); //black
	  }
	  SDL_RenderFillRect(renderer,&board);
	  }
	  } 
	*/
	SDL_RenderPresent(renderer);
	//wait 1/30th of a second
	SDL_Delay(1000/30);
          
      }
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  free(grid);
  return 0;
    
}
