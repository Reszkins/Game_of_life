test1.out: main.c matrix.c simulator.c
	cc main.c matrix.c simulator.c -o test1.out
test2.out: main2.c input.c output.c simulator.c matrix.c
	cc main2.c input.c output.c simulator.c matrix.c -o test2.out

