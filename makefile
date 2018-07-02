#makefile for the game of life

CC = gcc 
INCLUDES = -I.
#INCLUDES = -I./producer_consumer/ -I./queue/ -I./thread/

CFLAGS = -g -ansi -Werror -Wall -pedantic -pthread  $(INCLUDES)


bit.out : bits.o field.o my_barr.o chunks.o args.o thread.o files.o bit_manipulate.o getopts.o game.o 
	$(CC) $(CFLAGS) -o bit.out $^ 
	rm -f *.o

getopts.o : getopts.c getopts.h
	$(CC) -c $(CFLAGS) $<

bit_manipulate.o : bit_manipulate.c bit_manipulate.h
	$(CC) -c $(CFLAGS) $<

files.o : files.c files.h 
	$(CC) -c $(CFLAGS) $^ 

field.o : field.c field.h bit_manipulate.h
	$(CC) -c $(CFLAGS) $<

my_barr.o : my_barr.c my_barr.h 
	$(CC) -c $(CFLAGS) $<

chunks.o : chunks.c chunks.h 
	$(CC) -c $(CFLAGS) $^ 

args.o : args.c args.h 
	$(CC) -c $(CFLAGS) $^ 

thread.o : thread.c thread.h 
	$(CC) -c $(CFLAGS) $^ 

game.o : game.c game.h field.h bit_manipulate.h chunks.h args.h thread.h
	$(CC) -c $(CFLAGS) $^ 

bits.o : bits.c game.h
	$(CC) -c $(CFLAGS)  $< 	



clean :
	rm -f *.o
	rm -f bit.out
	rm -f *.gch
	rm -r files
