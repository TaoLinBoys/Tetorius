#include "pieces.h"
#include "board.h"
#include "tetris.h"

#define SDL_MAIN_HANDLED

//initial grid
int **grid;

//set window size
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 600;


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
int usedHold=0;
struct_piece currPiece;
struct_piece testPiece; //testing for collisions
struct_piece holdPiece;
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
  curr = 1;
  switch (pieceQueue[curr]){
  case 0: currPiece = I_BLOCK; testPiece = currPiece; break;
  case 1: currPiece = J_BLOCK; testPiece = currPiece; break;
  case 2: currPiece = L_BLOCK; testPiece = currPiece; break; 
  case 3: currPiece = O_BLOCK; testPiece = currPiece; break;
  case 4: currPiece = S_BLOCK; testPiece = currPiece; break; 
  case 5: currPiece = T_BLOCK; testPiece = currPiece; break;
  case 6: currPiece = Z_BLOCK; testPiece = currPiece; break;
  }
  switch (pieceQueue[curr-1]){
  case 0: holdPiece = I_BLOCK; break;
  case 1: holdPiece = J_BLOCK; break;
  case 2: holdPiece = L_BLOCK; break;
  case 3: holdPiece = O_BLOCK; break;
  case 4: holdPiece = S_BLOCK; break;
  case 5: holdPiece = T_BLOCK; break;
  case 6: holdPiece = Z_BLOCK; break;
  }
}
   
int nextPiece(){
  if (curr==7){  
    shuffle(pieceQueue); //execute when you have gotten all 7 pieces
    curr = 0;
  }
  curr+=1;
  usedHold=0;
  updateBoard();
  switch (pieceQueue[curr]){
  case 0: if(isDie(I_BLOCK,grid)) return 0; currPiece = I_BLOCK; testPiece = currPiece; break;
  case 1: if(isDie(J_BLOCK,grid)) return 0; currPiece = J_BLOCK; testPiece = currPiece; break;
  case 2: if(isDie(L_BLOCK,grid)) return 0; currPiece = L_BLOCK; testPiece = currPiece; break;
  case 3: if(isDie(O_BLOCK,grid)) return 0; currPiece = O_BLOCK; testPiece = currPiece; break;
  case 4: if(isDie(S_BLOCK,grid)) return 0; currPiece = S_BLOCK; testPiece = currPiece; break;
  case 5: if(isDie(T_BLOCK,grid)) return 0; currPiece = T_BLOCK; testPiece = currPiece; break;
  case 6: if(isDie(Z_BLOCK,grid)) return 0; currPiece = Z_BLOCK; testPiece = currPiece; break;
  }
  return 1;
}

int hold(){
  struct_piece temp;
  removeFromBoard();
  temp = holdPiece;
  holdPiece = currPiece;
  currPiece = temp;
  updateBoard();
}

int collidesAt(){
  int i;
  //printBoard();
  removeFromBoard();
  for(i=0;i<4;i++){
    int x = testPiece.x[i] + testPiece.xorigin;
    int y = testPiece.y[i] + testPiece.yorigin;
    if(x < 0 || x > 9 || y < 0 || y > 21 || grid[x][y]) {
      updateBoard();
      return 1;
    }
  }
  updateBoard();
  return 0;
}
   
//return 0 -> can't make move || return 1 -> possible move
int try(int action){ //{0:+rotate,1:-rotate,2:leftmove,3:rightmove,4:down}
  switch(action){
  case 0:
    //printf("rotating: in try\n");
    testPiece = rotate(testPiece,1);
    if (!collidesAt())return 1;
    else{return 0;}
 
  case 1:
    testPiece = rotate(testPiece,-1);
    if (!collidesAt())return 1;
    else{return 0;}
  
  case 2:
    testPiece = move(testPiece,-1);
    if (!(collidesAt())){ return 1;}
    else{return 0;}

  case 3:
    testPiece = move(testPiece,1);
    if (!collidesAt()) return 1;
    else{return 0;}

  case 4:
    testPiece = dropDown(testPiece);
    if(!collidesAt()) return 1;
    else{return 0;}

  }
}

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
  int score = 0;
  for (j=21;j>2;j--){
    gap=0;
    for (i=0;i<10;i++){
      if(!grid[i][j]){
	gap=1;
	break;
      }
    }
    if(!gap){
      deleteRow(j);
      score++;
      j++;
    }
  }
  return pow(2,score-1);
}




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
      initCurrPiece();
      updateBoard();
      drawBoard(renderer,1);
      
      //reset color blending
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

      int close_requested = 0;
      
      clock_t currenttime = clock();
      clock_t counter = clock();
      //playing the game
      while(!close_requested){
	if (currenttime - counter > 1000000){
	  if (try(4)){
	    removeFromBoard();
	    currPiece = dropDown(currPiece);
	    updateBoard();
	  }else{
	    if (nextPiece()){
	      P1_SCORE+= clearRows();
	      updateBoard();
	    }
	    else{
	      printf(">>P1_SCORE: %d\n",P1_SCORE);
	      SDL_Delay(3000);
	      close_requested=1;
	    }
	  }
	  counter = clock();
	}
	currenttime = clock();

	//process events
	SDL_Event event;
	while (SDL_PollEvent(&event)){
	  switch(event.type){
	  case SDL_QUIT:
	    close_requested = 1;
	    break;
	  case SDL_KEYDOWN:
	    switch(event.key.keysym.scancode){
	    case SDL_SCANCODE_RCTRL:
	      if (try(0)){
		removeFromBoard();
		currPiece = rotate(currPiece,1);
		updateBoard();
	      }
	      break;
	    case SDL_SCANCODE_LCTRL:
	      if (try(0)){
		removeFromBoard();
		currPiece = rotate(currPiece,1);
		updateBoard();
	      }
	      break;

	    case SDL_SCANCODE_UP:
	      if (try(1)){
		removeFromBoard();
		currPiece = rotate(currPiece,-1);
		updateBoard();
	      }
	      break;
	    case SDL_SCANCODE_LEFT:
	      if (try(2)){
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
	      }
	      break;
	    case SDL_SCANCODE_SPACE:
	      while (try(4)){
		removeFromBoard();
		currPiece = dropDown(currPiece);
	      }
	      if (nextPiece()){
		P1_SCORE+= clearRows();
	      }
	      updateBoard();
	      break;
	    case SDL_SCANCODE_RSHIFT:
	      if (!usedHold){
		hold();
		usedHold=1;
		updateBoard();
		colorHold(renderer,holdPiece);
	      }
	      break;
	    }
	  }
	}
	testPiece = currPiece;
	colorBoard(renderer,grid,1);
	SDL_RenderPresent(renderer);
      }

      //write score
      umask(0);
      int fd = open("coopscore.txt",O_CREAT | O_WRONLY, 0666);

      char score[10];
      sprintf(score,"%d",P1_SCORE);
      write(fd,score,strlen(score));
      close(fd);
      
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  free(grid);
  return 0;
}
