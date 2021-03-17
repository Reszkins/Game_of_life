test1.out: main.c matrix.c simulator.c
	cc main.c matrix.c simulator.c -o test1.out
glife: main2.c input.c output.c simulator.c matrix.c
	cc main2.c input.c output.c simulator.c matrix.c -o glife

