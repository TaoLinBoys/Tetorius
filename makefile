tetris: tetris.c pieces.c
	gcc tetris.c $(shell pkg-config --cflags --libs sdl2) pieces.c -o tetris

networking: server client

server: server.o networking.o
	gcc -o server server.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

server.o: server.c networking.h
	gcc -c server.c

client.o: client.c networking.h
	gcc -c client.c

networking.o: networking.c networking.h
	gcc -c networking.c

run:
	./tetris

run2:
	./tetris2

clean:
	rm tetris
	rm *~
