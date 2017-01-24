#include "pieces.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_MAIN_HANDLED

//initial grid
int **grid;

//set window size
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


//pieces
struct_piece I_BLOCK = {.type=1, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=1, .x[3]=2,
			.y[0]=0, .y[1]=0, .y[2]=0, .y[3]=0};
struct_piece J_BLOCK = {.type=2, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=1, .x[3]=-1,
			.y[0]=0, .y[1]=0, .y[2]=0, .y[3]=-1};
struct_piece L_BLOCK = {.type=3, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=1, .x[3]=1,
			.y[0]=0, .y[1]=0, .y[2]=0, .y[3]=-1};
struct_piece O_BLOCK = {.type=4, .xorigin=5, .yorigin=2,
			.x[0]=0, .x[1]=0, .x[2]=1, .x[3]=1,
			.y[0]=-1, .y[1]=0, .y[2]=-1, .y[3]=0};
struct_piece S_BLOCK = {.type=5, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=0, .x[3]=1,
			.y[0]=0, .y[1]=0, .y[2]=-1, .y[3]=-1};
struct_piece T_BLOCK = {.type=6, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=1, .x[3]=0,
			.y[0]=0, .y[1]=0, .y[2]=0, .y[3]=-1};
struct_piece Z_BLOCK = {.type=7, .xorigin=5, .yorigin=2,
			.x[0]=-1, .x[1]=0, .x[2]=1, .x[3]=0,
			.y[0]=-1, .y[1]=-1, .y[2]=0, .y[3]=0};

int curr;
struct_piece currPiece;
struct_piece testPiece; //testing for collisions
int pieceQueue[7];
int P1_SCORE;
int P2_SCORE;

int removeFromBoard(){
  int i;
  for (i=0;i<4;i++){
    int x=currPiece.xorigin + currPiece.x[i];
    int y=currPiece.yorigin + currPiece.y[i];
    grid[x][y]=0;
  }
}
int updateBoard(){
  int i;
  for (i=0;i<4;i++){
    int x=currPiece.xorigin + currPiece.x[i];
    int y=currPiece.yorigin + currPiece.y[i];
    printf("(x,y)%d: (%d,%d)\n",i,x,y);
    grid[x][y]=currPiece.type;
  }
}

//this is our backend board
int board(){
  int i,j;
  grid=(int**) malloc(sizeof(int*)*220);
  for(i=0; i<10; i++){
    grid[i]=(int*) malloc(sizeof(int)*22);
    for(j=0; j<22; j++){
      grid[i][j]=0;
    }
  }
}

//for debugging
int printBoard(){
  int i,j;
  for(i=0; i<22; i++){
    for(j=0; j<10; j++){
      printf("%d ",grid[j][i]);
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
  case 0: currPiece = I_BLOCK; testPiece = currPiece; break;
  case 1: currPiece = J_BLOCK; testPiece = currPiece; break;
  case 2: currPiece = L_BLOCK; testPiece = currPiece; break; 
  case 3: currPiece = O_BLOCK; testPiece = currPiece; break;
  case 4: currPiece = S_BLOCK; testPiece = currPiece; break; 
  case 5: currPiece = T_BLOCK; testPiece = currPiece; break;
  case 6: currPiece = Z_BLOCK; testPiece = currPiece; break;
  }
}
   
int nextPiece(){
  if (curr=7){  
    shuffle(pieceQueue); //execute when you have gotten all 7 pieces
    curr = 0;
  }
  curr++;
  printf("curr= %d\n",curr);
  updateBoard();
  printBoard();
  switch (pieceQueue[curr]){
  case 0: currPiece = I_BLOCK; testPiece = currPiece; break;
  case 1: currPiece = J_BLOCK; testPiece = currPiece; break;
  case 2: currPiece = L_BLOCK; testPiece = currPiece; break; 
  case 3: currPiece = O_BLOCK; testPiece = currPiece; break;
  case 4: currPiece = S_BLOCK; testPiece = currPiece; break; 
  case 5: currPiece = T_BLOCK; testPiece = currPiece; break;
  case 6: currPiece = Z_BLOCK; testPiece = currPiece; break;
  }
}

int collidesAt(){
  int i;
  //printBoard();
  removeFromBoard();
  for(i=0;i<4;i++){
    int x = testPiece.x[i] + testPiece.xorigin;
    printf("--collidesAt x: %d \n" ,x);
    int y = testPiece.y[i] + testPiece.yorigin;
    if(x < 0 || x > 9 || y < 0 || y > 21 || grid[x][y]) {
      printf("out of boundaries\n");
      updateBoard();
      return 1;
    }
  }
  updateBoard();
  //printf("--doesn't collide\n");
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
      printf("-After Rotate- Piece x,y:(%d,%d) \n",Piece.x[j],Piece.y[j]);
    }
  }
  if (i<0){  //counterclockwise rotation
    for (j=0; j<4;j++){
      int newX = Piece.y[j] * (-1);
      int newY = Piece.x[j];
      Piece.x[j] = newX;
      Piece.y[j] = newY;
      printf("Piece.x[j]:%d \n Piece.y[j]:%d \n",Piece.x[j],Piece.y[j]);
    }
  }
  return Piece;
}
int isLowest(struct_piece Piece){
  int i,y;
  for(i=0;i<4;i++){
    y = Piece.y[i] + Piece.yorigin;
    printf("piece[y]: %d \n",y);
    if (y+1>21) return 1;
  }
  return 0;
}

struct_piece move(struct_piece Piece,int displacement){
  Piece.xorigin+=displacement;
  return Piece;
}


/*
int resetTestPiece(){
  //testPiece = currPiece;
  testPiece.type = currPiece.type;
  testPiece.xorigin = currPiece.xorigin;
  testPiece.yorigin = currPiece.yorigin;
  int i;
  for(i=0;i<4;i++){
    testPiece.x[i] = currPiece.x[i];
    testPiece.y[i] = currPiece.y[i];  
  }
  //printf("reseted test piece\n");
  return 1;
}*/

//return 0 -> can't make move || return 1 -> possible move
int try(int action){ //{0:+rotate,1:-rotate,2:leftmove,3:rightmove,4:down}
  switch(action){
  case 0:
    //printf("rotating: in try\n");
    rotate(testPiece,1);
    removeFromBoard();
    //printBoard();
    //printf("just removed from board\n");
    updateBoard();
    testPiece = currPiece;
    if (!collidesAt())return 1;
    else{return 0;}
 
  case 1:
    rotate(testPiece,-1);
    testPiece = currPiece;
    return 1;
    if (!collidesAt())return 1;
    else{return 0;}
  
  case 2:
    testPiece = move(testPiece,-1);
    printf("AFTER MOVE xorigin of testpiece:%d \n", testPiece.xorigin);
    printf("!collidesAt(): %d\n",!collidesAt());
    if (!(collidesAt())){ return 1;}
    else{
      printf("does collide\n");
      return 0;}

  case 3:
    testPiece = move(testPiece,1);
    printf("AFTER MOVE xorigin of testpiece:%d \n", testPiece.xorigin);
    if (!collidesAt()) return 1;
    else{return 0;}

  case 4:
    if (isLowest(testPiece)) return 0;
    else{ return 1;}
  }
}

int isDie(){
  return collidesAt(currPiece);
}

//this is prob wrong. i'll fix later
int deleteRow(int row){
  int i,j;
  for (j = row-1; j > 2; j--) {
    for (i = 0; i < 10; i++) {
      grid[i][j+1] = grid[i][j];
    }
  }
}
int clearRows(){
  int gap,j,i;
  for (j=22;j>2;j--){
    gap=0;
    for (i=0;i<10;i++){
      if(!grid[i][j]){
	gap=1;
	break;
      }
    }
    if(!gap){
      deleteRow(j);
      j+=1;
    }
  }
return 1;
}
  /*
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
  if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) < 0 ){
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
      //set background color to black
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      
      //INITIALIZING BOARD AND PIECES (backend)
      board();
      printf("board initialized\n");
      //initPieces(I_BLOCK,J_BLOCK,L_BLOCK,O_BLOCK,S_BLOCK,T_BLOCK,Z_BLOCK);
      printf("I_BLOCK.xorigin=%d\n",I_BLOCK.xorigin);
      initCurrPiece();
      printf("curr = %d, pieceQueue[curr] = %d\n",curr,pieceQueue[curr]);
      updateBoard();
      drawBoard(renderer,1);

      //reset color blending
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

      int close_requested = 0;
      clock_t counter = clock();
      while(!close_requested){
	/*
  //clear rows, updateboard
	if (clock() - counter > 1000){
	    if (try(4)){
        removeFromBoard();
        currPiece = dropDown(currPiece);
        updateBoard();
        counter = clock();
      }
      if(isLowest(currPiece)){
        nextPiece();
      }
      }*/

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
	      if (try(0)){
		//printf("rotating now\n");
		removeFromBoard();
		currPiece = rotate(currPiece,1);
		updateBoard();
		//printBoard();
	      }
	      break;
	    case SDL_SCANCODE_RCTRL:
	      if (try(1)){
		removeFromBoard();
		currPiece = rotate(currPiece,-1);
		updateBoard();
	      }
	      break;
	    case SDL_SCANCODE_LEFT:
	      if (try(2)){
		printf("going to move left\n");
		removeFromBoard();
		currPiece = move(currPiece,-1);
		updateBoard();
	      }
	      break;
	    case SDL_SCANCODE_RIGHT:
	      if (try(3)){
		removeFromBoard();
		currPiece = move(currPiece,1);
		updateBoard();
	      }
	      break;
	    case SDL_SCANCODE_DOWN:
	      if (try(4)){
		removeFromBoard();
		currPiece = dropDown(currPiece);
		updateBoard();
		printf("printing board after dropdown now--");
		//printBoard();	
	      }
	      break;
	    }
	    //printBoard();
	  }
	}
	testPiece = currPiece;
	colorBoard(renderer,grid,1);
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
