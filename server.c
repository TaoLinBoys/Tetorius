#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#include "networking.h"

void process( char * s );
void sub_server( int sd );

int coopPlayers = 0;
char coopMsg1[] = "WAITING FOR SECOND PLAYER";
char coopMsg2[] = "STARTING GAME";
char coopMsg3[] = "WAITING FOR LOBBY TO EMPTY";

int main() {

  int sd, connection;

  sd = server_setup();
    
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
    runGame( buffer );
    write( sd, buffer, sizeof(buffer));    
  }
  
}


void runGame( char * s ) {
  if(strcmp(s, "coop") == 0){
    if(coopPlayers == 0){
      coopPlayers++;
      write( sd, coopMsg1, sizeof(coopMsg1));
    }
    if(coopPlayers == 1){
      coopPlayers++;
      write( sd, coopMsg2, sizeof(coopMsg2));
    }
    if(coopPlayers == 2){
      write( sd, coopMsg3, sizeof(coopMsg3));
    }
  }
}

