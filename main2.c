#include "matrix.h"
#include "input.h"
#include "output.h"
#include "simulator.h"

#include <stdio.h>
#include <string.h>


int main(int argc,char **argv){

	arguments args;

	init_cfg(&args);
	
	process_input(argc,argv,&args);

	int e=check_error();
	if(e != 0) return e;

	if(args.help_wanted == 1){
	     	display_help();
		return 1;
	}
	
	matrix world = read_matrix(args.in);

	for(int i=0; i < args.iterations; i++){

		save(world, &args);
		
		if(strcmp(args.game,"glife") == 0)
			next_generation(&world);
		else if(strcmp(args.game,"ant") == 0)
			ant_next_generation(&world);

	}

	free_matrix(&world);

	return 0;
}
