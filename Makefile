test1.out: main.c matrix.c simulator.c
	cc main.c matrix.c simulator.c -o test1.out
glife: main2.c input.c output.c simulator.c matrix.c
	cc main2.c input.c output.c simulator.c matrix.c gifenc.o -o glife -lm

gifenc.o: lib/gifenc.c
	cc -c lib/gifenc.c -o gifenc.o