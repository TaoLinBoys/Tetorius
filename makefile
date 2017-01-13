tetris: tetris.c
	gcc tetris.c $(shell pkg-config --cflags --libs sdl2) -o tetris
run:
	./tetris
clean:
	rm tetris
	rm *~
