glife: main.c input.c output.c simulator.c matrix.c gifenc.o
	cc main.c input.c output.c simulator.c matrix.c gifenc.o -o glife -lm

gifenc.o: lib/gifenc.c
	cc -c lib/gifenc.c -o gifenc.o
