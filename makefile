compile: tetris.c
	gcc -I/usr/include/SDL2/ tetris.c -o tetris -lSDL2 

run: tetris
