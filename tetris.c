#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
#include "SDL2/SDL.h"

#define SDL_MAIN_HANDLED

//set window size
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//set board size
const int BOARD_WIDTH = 250;
const int BOARD_HEIGHT = 600;

//set board displacement from top left corner of window
const int P1_DISPLACEMENT_X = 50;
const int P1_DISPLACEMENT_Y = 50;
const int P2_DISPLACEMENT_X = 300;
const int P2_DISPLACEMENT_Y = 50;

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
int **grid;

//this is our backend board
int board(){
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
int printBoard(){
  int i,j;
  for(i=0; i<26; i++){
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

//helpr functions
int swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int shuffle(int arr[]) {
  srand(time(NULL));
  int i;
  for(i = 7; i > 0; i--) {
    int j = rand() % (i+1);
    swap(&arr[i], &arr[j]);
    //printf("pieces[%d] = %d",i,arr[j]);
  }
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


//int isLowest : tests if the piece can go any lower

int move(struct_piece Piece,int x){
  Piece.xorigin+=x;
  return 1;
}

int dropDown(struct_piece Piece){
  Piece.yorigin++;
  return 1;  
}

int updateBoard(){ //doesn't work properly
  int i;
  for (i=0;i<4;i++){
    int x=testPiece.xorigin + testPiece.x[i];
    int y=testPiece.yorigin + testPiece.y[i];
    grid[x][y]=1;
  }
}

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

//KEYBOARD EVENTS
ex:
int close_requested = 0;

while(!close_requested){
  //process events
  SDL_Event event;
  while (SDL_PollEvent(&event)){
    case SDL_QUIT:
      close_requested = 1;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.scancode){
        case SDL_SCANCODE UP:
          //do stuff
          break;
        case SDL_SCANCODE DOWN:
          //do stuff
          break;
      }

    }
  }
}

  if(event->key.keysym.scancode != SDL_GetScancodeFromKey(event->key.keysym.sym))
    printf("Physical %s key acting as %s key",
      SDL_GetScancodeName(event->key.keysym.scancode),
      SDL_GetKeyName(event->key.keysym.sym));



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
	/*
	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	//Fill the surface white
	SDL_FillRect(screenSurface,
		     NULL,
		     SDL_MapRGB(screenSurface->format, 0, 0, 0));
	
	SDL_RenderClear( renderer );
	*/

	//need to fix to match the size of the sdl window?? i think
	//background
	
	int row;
	for(row = 0; row <= 24; row++){
	  printf("haha");
	  SDL_RenderDrawLine(renderer,P1_DISPLACEMENT_X,row*25,BOARD_WIDTH, row*20);
	  SDL_RenderPresent(renderer);
        }
	

	//INITIALIZING BOARD AND PIECES
	board();
	initPieces(I_BLOCK,J_BLOCK,L_BLOCK,O_BLOCK,S_BLOCK,T_BLOCK,Z_BLOCK);
	initCurrPiece();
	//updateBoard(); //update board doesn't work properly
	printBoard();
	printf("curr = %d, pieceQueue[curr] = %d\n",curr,pieceQueue[curr]);
	//printBoard();




	//Drawing Board
	SDL_Rect board;
	board.x = P1_DISPLACEMENT_X;
	board.y = P1_DISPLACEMENT_Y;
	board.w = BOARD_WIDTH;
	board.h = BOARD_HEIGHT;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderDrawRect(renderer,&board);
	SDL_RenderPresent(renderer);
	
 
	/*
	SDL_RenderFillRect(renderer,&block3);
	*/
	
	
      
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
		if (try(0)) rotate(currPiece,1);
	      case SDL_SCANCODE_RCTRL:
		if (try(1)) rotate(currPiece,-1);
	      case SDL_SCANCODE_LEFT:
		if (try(2)) move(currPiece,-1);
	      case SDL_SCANCODE_RIGHT:
		if (try(3)) move(currPiece,1);
	      case SDL_SCANCODE_DOWN:
		if (try(4)) dropDown(currPiece);
	      }
	      //save
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

	  int i,j;
	  SDL_Rect currentRect = {.w = 25,.h=25};
	  for(i=0; i<26; i++){
	    for(j=0; j<10; j++){
	      currentRect.x = i*25;
	      currentRect.y = j*25;
	      SDL_SetRenderDrawColor(renderer,255,0,0,0);
	      SDL_RenderFillRect(renderer,&board);
	    }
	  } 
	  SDL_RenderPresent(renderer);

	  //wait 1/30th of a second
	  SDL_Delay(1000/30);
  
	  //SDL_RenderClear(renderer);
	  //changes to window
	  //SDL_
	  //sleep(1000);
	  //updateBoard();
	  //
	  //endwhile
	}
      }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    
}
