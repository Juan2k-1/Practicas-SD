CFLAGS=-Wall
CC=gcc

all: sudokuad

sudokuad: sudokuad.o GestorJuegos_svc.o GestorJuegos_xdr.o
	$(CC) -o $@ sudokuad.o GestorJuegos_svc.o GestorJuegos_xdr.o

sudokuad.o: GestorJuegos.h

clean: 
	rm *.o 
