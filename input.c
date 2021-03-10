#include "matrix.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_help(){
	printf("POMOC\n");
}

void process_input(int argc, char **argv, arguments *args){
	char c;
	int x = 1;
	
	while(1){
		if(x >= argc) break;

		if(c=argv[x][0] == '-')
			c = argv[x][1];
		
		x++;

		switch(c){
			case 'h':
				args->help_wanted = 1;
				break;
			case 'i':
				args->iterations = atoi(argv[x]);
		       		x++;
				break;	
			case 'f':
				if(strcmp("stdin",argv[x])==0)
					args->input = stdin;
				else args->input = fopen(argv[x], "r");
				args->in = argv[x];
				x++;
				break;
			case 'o':
				if(strcmp("stdout",argv[x])==0)
					args->output = stdout;
				else args->output = fopen(argv[x], "w");
				args->out = argv[x];
				x++;
				break;
		}

	}

}


matrix read_matrix(FILE *in){

	int x;
	fscanf(in,"%d",&x);
	int y;
	fscanf(in,"%d",&y);
	matrix M;
	create_matrix(x,y,&M);

	for(int i=0; i < x; i++){
		for(int j=0; j < y; j++){
			fscanf(in,"%d",&M.v[i][j]);
		}
	}

	return M;
}	


