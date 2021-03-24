#include "matrix.h"
#include "input.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_rules(arguments *args, char* rules) // ustawia reguły gry
{
	int length = strlen(rules);
	int i=0, s=0, b=0;
	if(rules[i]=='B') i++;
	while(rules[i] != '/')
	{
		if(rules[i] <= '9' && rules[i] >= '0')
		{
			args->birth[b] = rules[i] - '0';
			b++;
			i++;
		}
	}
	i++;
	if(rules[i]=='S') i++;
	while(rules[i] != '\0')
	{
		if(rules[i] <= '9' && rules[i] >= '0')
		{
			args->survival[s] = rules[i] - '0';
			s++;
			i++;
		}
	}
	for(;b<9;b++) args->birth[b] = -1;
	for(;s<9;s++) args->survival[s] = -1;
}

void process_input(int argc, char **argv, arguments *args){	// przetworzenie argumentów wejściowych
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

		switch(c){					// czytanie argumentów
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
			case 'r':
				set_rules(args, argv[x]);
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

matrix read_matrix(char *filename){	// wczytanie świata z pliku wejściowego
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

void init_cfg(arguments *args){		// ustalenie wartości argumentów na domyślne
	args->help_wanted = 0;
	args->iterations = 100;
	strcpy(args->in, "dane");
	//args->input = NULL;
	strcpy(args->out, "wynik");
	args->output = NULL;
	strcpy(args->format, "gif");
	strcpy(args->game, "glife");
	set_rules(args, "3/23");
}
