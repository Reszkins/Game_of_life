#include "matrix.h"
//#include ...

#include <stdio.h>


int main(int argc,char **argv){

	arguments args;

	process_input(argc,argv,&args);

	if(args.help == 1){

	     	display_help();
		return 1;
	}
	
	matrix world = read_matrix(args.file);

	for(int i=0; i < args.iterations; i++){

		write_world(args.output);
		next_generation(&world);

	}
	return 0;
}
