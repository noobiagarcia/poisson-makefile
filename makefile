CC=gcc
CFLAGS=-l.



poissonmake: poissonmake.o poissonfunc.o

	$(CC) -o poissonmake poissonmake.o poissonfunc.o -lm
