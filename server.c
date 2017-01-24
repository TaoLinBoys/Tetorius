#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#include "networking.h"

void runGame( char * s , int sd );
void sub_server( int sd );

int coop = 0;
int p1, p2; //sock desc of player 1 and 2
char coopMsg1[] = "WAITING FOR SECOND PLAYER";
char coopMsg2[] = "STARTING GAME";
char coopMsg3[] = "WAITING FOR LOBBY TO EMPTY";

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
    //write( sd, buffer, sizeof(buffer));    
  }
  
}


void runGame( char * s , int sd ) {
  if(strcmp(s, "coop") == 0){
    //printf("%d\n", coop);
    if(coop == 0){
      coop++;
      //printf("%d\n", coop);
      p1 = sd;
      //s = coopMsg1;
      write( sd, coopMsg1, sizeof(coopMsg1));
    }
  }
}

