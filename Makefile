build.c:
	gcc -c *.c

build:	build.c 
	gcc OrdenacaoExterna2.o main.o -lm -o run
clear:
	rm *.o

all: build.c build clear

