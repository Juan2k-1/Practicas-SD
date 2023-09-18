CFLAGS=-Wall
CC=gcc

all: sudoku

sudoku: sudoku.o GestorJuegos_clnt.o GestorJuegos_xdr.o
	$(CC) -o $@ sudoku.o GestorJuegos_clnt.o GestorJuegos_xdr.o

sudoku.o: GestorJuegos.h

clean:
	rm *.o 
