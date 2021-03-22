#include "matrix.h"
#include "input.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_help(){				// ta funkcja powinna być w kodzie z obsługą wyjścia, a nie wejścia
	printf("Usage: ./glife [arguments]\n");
	printf("Arguments:\n");
	printf("-h 							=> help\n");
	printf("-g (with one of:[glife, ant]				=> game\n");
	printf("-f (with filename or stdin) 				=> input file\n");
	printf("-o (with filename prefix) 				=> output file prefix\n");
	printf("-t (with one of:[gif, jpg, png, bmp, txt, stdout]) 	=> output file type\n");
	printf("-i (with integer number) 				=> number of iterations\n");
}

void process_input(int argc, char **argv, arguments *args){
	char c;
	int x = 1;
	
	while(1){
		if(x >= argc) break;

		if(c=argv[x][0] == '-')
			c = argv[x][1];
		else{
		       	error(1);
			break;
		}
		
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
				strcpy(args->in, argv[x]);
				x++;
				break;
			case 'o':
				strcpy(args->out, argv[x]);
				x++;
				break;
			case 't':
				strcpy(args->format, argv[x]);
				x++;
				break;
			case 'g':
				strcpy(args->game, argv[x]);
				x++;
				break;
		}

	}
}

int is_type(arguments cfg, const char* type)
{
	if(!strcmp(cfg.format, type)) return 1;
	return 0;
}

matrix read_matrix(char *filename){
	FILE *in = strcmp(filename, "stdin") == 0 ? stdin : fopen(filename, "r");
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

	fclose(in);
	return M;
}	

void init_cfg(arguments *args){
	args->help_wanted = 0;
	args->iterations = 100;
	strcpy(args->in, "dane");
	//args->input = NULL;
	strcpy(args->out, "wynik");
	args->output = NULL;
	strcpy(args->format, "gif");
	strcpy(args->game, "glife");
}
