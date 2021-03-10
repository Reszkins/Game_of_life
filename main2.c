#include "matrix.h"
#include "input.h"
#include "output.h"
#include "simulator.h"

#include <stdio.h>


int main(int argc,char **argv){

	arguments args;

	process_input(argc,argv,&args);

	printf("help_wanted: %d\n",args.help_wanted);
	printf("iterations: %d\n",args.iterations);
	printf("out: %s\n",args.out);
	printf("in: %s\n",args.in);
	

	if(args.help_wanted == 1){

	     	display_help();
		return 1;
	}
	
	matrix world = read_matrix(args.input);

	for(int i=0; i < args.iterations; i++){

		write_world(world,args.output,args.out);
		next_generation(&world);

	}
	return 0;
}
