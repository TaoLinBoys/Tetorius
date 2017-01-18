#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
//#include <time.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int BOARD_WIDTH = 250;
const int BOARD_HEIGHT = 600;

const int P1_DISPLACEMENT_X = 50;
const int P1_DISPLACEMENT_Y = 50;
const int P2_DISPLACEMENT_X = 300;
const int P2_DISPLACEMENT_Y = 50;


typedef struct piece{
  int rotation;
  int x1;int y1; //coords of 4 blocks of tetromino
  int x2;int y2;
  int x3;int y3; 
  int x4;int y4;
} struct_piece;

struct piece T_BLOCK; 
struct piece I_BLOCK;
struct piece O_BLOCK;
struct piece S_BLOCK;
struct piece Z_BLOCK;
struct piece L_BLOCK;
struct piece J_BLOCK; 
//piece allPieces[]={T_BLOCK,I_BLOCK,O_BLOCK,S_BLOCK,Z_BLOCK,L_BLOCK,J_BLOCK};

/*
int curr;
int pieceQueue[];
int x ; int y; //coords of origin of piece on the gameboard

if (curr=7){  
  shuffle(pieceQueue); //execute when you have gotten all 7 pieces
  curr = 0;
}

//helpr functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int arr[]) {
    srand(time(NULL));
    int i;
    for(i = 7; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
	printf("pieces[%d] = %d",i,arr[j])
    }
}

int collidesAt(int x,int y){
 asjpdopadop
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
//this is our backend board
int board(){
  int i,j;
  int** grid=(int**) malloc(sizeof(int*)*260);
  for(i=0; i<10; i++){
    grid[i]=(int*) malloc(sizeof(int)*10);
    for(j=0; j<26; j++){
      grid[i][j]=0;
    }
  }
}

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
	//Drawing Rect test
	
	SDL_Rect recttest;
	recttest.x = P1_DISPLACEMENT_X;
	recttest.y = P1_DISPLACEMENT_Y;
	recttest.w = BOARD_WIDTH;
	recttest.h = BOARD_HEIGHT;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderDrawRect(renderer,&recttest);
	SDL_RenderPresent(renderer);
	//Update the surface
	//SDL_UpdateWindowSurface(window);
	
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
