#Tetris
Featuring both singleplayer and multiplayer!

##Brought to you by:
Michael Woo Pd5, Tao Lin Pd10, Harry Lum Pd10

##Libraries Required:
SDL2
"apt-get install libsdl2-dev"

##To compile, simply type make in a terminal.
./server in a terminal

./client in another terminal

Follow the prompts asking for either single/coop mode.

Type "make run" in terminal to play singleplayer if network connection doesn't work.

##List of files:
board.c

board.h

client.c

makefile

networking.c

networking.h

pieces.c

pieces.h

server.c

tetris.c

tetris.h

#How to Play:
##Keys:
Up - rotate clockwise

RCtrl - rotate counterclockwise

Down - drop down slowly

Left/Right - move piece left/right

RShift - hold(save) piece

Space - harddrop(instantly drop piece to the bottom)

##Goal: 
Clear Lines to increase your score. Clearing more lines at once gets you more points.

If pieces fill up the spawn area of your next piece, you lose.

In coop mode, the player with the higher score wins.

##Bugs:
Sometimes graphics doesn't work properly. Simply recompile the files and rerun.

Timer works differently on some computers. The gravity in the game may be extremely fast or slow. Professionals can play with both.

Game may not end when it should. Wait until the natural softdrop occurs.

Networking hasn't been tested on school computers, and thus, may be dysfunctional. 

##Cool Features:
Try a T-spin!
