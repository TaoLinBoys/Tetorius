#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

char coopMsg1[] = "WAITING FOR SECOND PLAYER";
char coopMsg2[] = "STARTING GAME";
char coopMsg3[] = "WAITING FOR LOBBY TO EMPTY";

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
    printf("pick gamemode: [single/coop]");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
  
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    
    if(strcmp(buffer, "single") == 0){
      //launch game
      system("tetris");
    }else if(strcmp(buffer, coopMsg1) == 0){
      printf("%s\n", buffer);
      write( sd, "coop", sizeof("coop") );
    }else if(strcmp(buffer, coopMsg2) == 0){
      printf("%s\n", buffer);
      system("tetris"); //change this
    }else if(strcmp(buffer, coopMsg3) == 0){
      printf("%s\n", buffer);
      sleep(5000);
      write( sd, "coop", sizeof("coop") );
    }
  
  return 0;
}
