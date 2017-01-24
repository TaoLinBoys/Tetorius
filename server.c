#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "networking.h"

void runGame( char * s , int sd );
void sub_server( int sd );

int coop = 0;
int p1, p2; //sock desc of player 1 and 2
char coopMsg1[] = "WAITING FOR SECOND PLAYER";
char coopMsg2[] = "PLAYER2 HAS JOINED";
char coopMsg3[] = "WAITING FOR LOBBY TO EMPTY";
char returnWait[] = "wait";
char returnRun[] = "runscore";
char returnFull[] = "Room is currently full";

int main() {

  int sd, connection;
  
  sd = server_setup();
  printf("[server] WAITING FOR CONNECTION... \n");  
  while (1) {

    connection = server_connect( sd );

    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      close( connection );
    }
  }
  return 0;
}


void sub_server( int sd ) {

  char buffer[MESSAGE_BUFFER_SIZE];
  while (read( sd, buffer, sizeof(buffer) )) {

    printf("[SERVER %d] received: %s\n", getpid(), buffer );
    runGame( buffer , sd );
  }
  
}


void runGame( char * s , int sd ) {
  if(strcmp(s, "coop") == 0){


    //room empty
    if(coop == 0){
      coop++;
      printf("%d\n", coop);
      write( sd, coopMsg1, sizeof(coopMsg1) );
      while(coop == 1){}
      write( sd, coopMsg2, sizeof(coopMsg2) );
    }



    //only one person
    else if(coop == 1){
      coop++;
      printf("%d\n", coop);
      write( sd, returnRun , sizeof(returnRun) );
    }



    //room is full, denies access
    else if(coop == 2){
      write( sd, returnFull,sizeof(returnFull) );
    }
  }
}


