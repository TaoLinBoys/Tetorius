#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

int coop = 0;
char coopMsg1[] = "WAITING FOR SECOND PLAYER";
char coopMsg2[] = "STARTING GAME";
char coopMsg3[] = "WAITING FOR LOBBY TO EMPTY";
char returnWait[] = "wait";
char returnRun[] = "runscore";
char returnFull[] = "Room is currently full";
int score;

int main( int argc, char *argv[] ) {

  char *host;
  if (argc != 2 ) {
    printf("host not specified, conneting to 127.0.0.1\n");
    host = "127.0.0.1";
  }
  else
    host = argv[1];
  
  int sd;

  sd = client_connect( host );

  char buffer[MESSAGE_BUFFER_SIZE];
  
  while (1) {
    printf("pick gamemode: [single/coop] \n");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
  
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );

    //singleplayer
    if(strcmp(buffer, "single") == 0){
      int temp = fork();
      if( temp == 0 ){
	system("./tetris");
      }
    }


    //waiting for a second player
    else if(strcmp(buffer, coopMsg1) == 0){
      printf("%s\n", buffer);
      char temp[256];
      read( sd, temp, 256 );//gets a response when another player joins
      int tempF = fork();
      if( tempF == 0 ){
	system("./tetris");
      }
    }


    
    //room's full
    else if(strcmp(buffer, returnFull) == 0){
      printf("%s\n", buffer);
    }
  }

  return 0;
}
