#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
//#include <time.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//each block is 25x25
const int BOARD_WIDTH = 250;
const int BOARD_HEIGHT = 600;

const int P1_DISPLACEMENT_X = 50;
const int P1_DISPLACEMENT_Y = 50;
const int P2_DISPLACEMENT_X = 300;
const int P2_DISPLACEMENT_Y = 50;


typedef struct piece{
  int rotation;
  int x[4];
  int y[4];
  int xorigin;
  int yorigin;
  /*
  int x1;int y1; //coords of 4 blocks of tetromino
  int x2;int y2;
  int x3;int y3; 
  int x4;int y4;
  */
} struct_piece;

struct_piece I_BLOCK;
struct_piece J_BLOCK;
struct_piece L_BLOCK;
struct_piece O_BLOCK;
struct_piece S_BLOCK;
struct_piece T_BLOCK;
struct_piece Z_BLOCK;

int initPieces(){
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
  O_BLOCK.x[0] = -1;
  O_BLOCK.y[0] = 0;
  O_BLOCK.x[1] = 0;
  O_BLOCK.y[1] = 0;
  O_BLOCK.x[2] = 1;
  O_BLOCK.y[2] = 0;
  O_BLOCK.x[3] = 2;
  O_BLOCK.y[3] = 0;
  //struct_piece S_BLOCK;
  S_BLOCK.rotation = 0;
  S_BLOCK.xorigin = 5;
  S_BLOCK.yorigin = 2;
  S_BLOCK.x[0] = -1;
  S_BLOCK.y[0] = 0;
  S_BLOCK.x[1] = 0;
  S_BLOCK.y[1] = 0;
  S_BLOCK.x[2] = 1;
  S_BLOCK.y[2] = 0;
  S_BLOCK.x[3] = 2;
  S_BLOCK.y[3] = 0;
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
  T_BLOCK.x[3] = 2;
  T_BLOCK.y[3] = 0;
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
//struct_piece allPieces[]={I_BLOCK,J_BLOCK,L_BLOCK,O_BLOCK,S_BLOCK,T_BLOCK,Z_BLOCK};


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

int nextPiece(){
  if (curr=7){  
    shuffle(pieceQueue); //execute when you have gotten all 7 pieces
    curr = 0;
  }
  curr++;
  printf("curr= %d",curr);
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
	printf("pieces[%d] = %d",i,arr[j]);
    }
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


int collidesAt(struct_piece Piece){
  int i;
  for(i=0;i<4;i++){
    int x = Piece.x[i] + Piece.xorigin;
    int y = Piece.y[i] + Piece.yorigin;
    if(!grid[x][y]) return 1; 
  }
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

/*
int updateBoard(){
int i;
for (i=0;i<4;i++){
   int x=testPiece.xorigin + testPiece.x[i];
   int y=testPiece.yorigin + testPiece.y[i];
   grid[x][y]=1;
}
}

//this is prob wrong. i'll fix later
int deleteRow(int row){
  for (int j = row-1; j > 0; j--) {
      for (int i = 1; i < 11; i++) {
        board[i-1][j+2] = board[i-1][j+1];
      }
    }
  return 1;
  }
 

int isDie(){
  return collidesAt(currPiece);
}

 */




/*
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

//just some stuff im considering and looking at later. don't worry about this
  private final Point[][][] Tetraminos = {
    // I-Piece
    {
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(3, 1) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(1, 3) },
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(3, 1) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(1, 3) }
    },
    
    // J-Piece
    {
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(2, 0) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(2, 2) },
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(0, 2) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(0, 0) }
    },
    
    // L-Piece
    {
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(2, 2) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(0, 2) },
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(0, 0) },
      { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(2, 0) }
    },
    
    // O-Piece
    {
      { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
      { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
      { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
      { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) }
    },
    
    // S-Piece
    {
      { new Point(1, 0), new Point(2, 0), new Point(0, 1), new Point(1, 1) },
      { new Point(0, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) },
      { new Point(1, 0), new Point(2, 0), new Point(0, 1), new Point(1, 1) },
      { new Point(0, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) }
    },
    
    // T-Piece
    {
      { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(2, 1) },
      { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) },
      { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(1, 2) },
      { new Point(1, 0), new Point(1, 1), new Point(2, 1), new Point(1, 2) }
    },
    
    // Z-Piece
    {
      { new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(2, 1) },
      { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(0, 2) },
      { new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(2, 1) },
      { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(0, 2) }
    }
  };

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
      /*
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        SDL Renderer* rend = SDL_CreateRenderer(win,-1,render_flags)
        if (!rend)
        {
	printf("error creating renderer: %s\n", SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();
        }
      */
      renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	       
      if( window == NULL ){
	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      }
      else{
	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	//Fill the surface white
	SDL_FillRect(screenSurface,
		     NULL,
		     SDL_MapRGB(screenSurface->format, 0, 0, 0));
	
	SDL_RenderClear( renderer );
	
	//need to fix to match the size of the sdl window?? i think
	//background
	/*
	int row;
	for(row = 0; row <= 24; row++){
	  printf("haha");
	  SDL_RenderDrawLine(renderer,0,row*20,SCREEN_WIDTH, row*20);
	  SDL_RenderPresent(renderer);
	}
	*/

	//testing stuff
	board();
	printBoard();




	//Drawing Board
	SDL_Rect board;
	board.x = P1_DISPLACEMENT_X;
	board.y = P1_DISPLACEMENT_Y;
	board.w = BOARD_WIDTH;
	board.h = BOARD_HEIGHT;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderDrawRect(renderer,&board);
	SDL_RenderPresent(renderer);

	//Drawing a block

	//doesnt work
	/*
	struct_piece* piece = I_BLOCK;
	SDL_SetRenderDrawColor( renderer, 102,51,153,255);
	SDL_Rect block1 = {.x = piece->x1, .y = piece->y1,
			   .w = 25, .h = 25,};
	SDL_Rect block2 = {.x = piece->x2, .y = piece->y2,
			   .w = 25, .h = 25,};
	SDL_Rect block3 = {.x = piece->x3, .y = piece->y3,
			   .w = 25, .h = 25,};
	SDL_Rect block4 = {.x = piece->x4, .y = piece->y4,
			   .w = 25, .h = 25,};
	SDL_RenderFillRect(renderer,&block1);
	SDL_RenderFillRect(renderer,&block2);
	SDL_RenderFillRect(renderer,&block3);
	SDL_RenderFillRect(renderer,&block4);
	SDL_RenderPresent(renderer);
	*/
	

	
	int close_requested = 0;

	while(!close_requested){
	  //process events
	  SDL_Event event;
	  while (SDL_PollEvent(&event)){
	     if (event.type ==SDL_QUIT){  
	      close_requested = 1;       
	      SDL_DestroyWindow( window );
	      SDL_Quit();
	      break;
	     }
	  }
	}
      }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    
}
