#include "matrix.h"

void display_help(){
	printf("POMOC\n");
}

matrix process_input(int argc, char **argv){
	char c;
	int x = 1;
	arguments args;
	while(1){
		if(x => argc) break;

		if(c=getc(argv[x]) == '-')
			c = getc(argv[x]);
		
		x++;

		switch(c){
			case 'h':
				args.help_wanted = 1;
				break;
			case 'i':
				args.iterations = atoi(argv[x]);
		       		x++;
				break;	
			case 'f':
				args.file = fopen(argv[x], "r");
				x++;
				break;
			case 'o':
				args.output = fopen(argv[x], "w");
				x++;
				break;
		}

	}

}


matrix read_matrix(FILE *in){

	int x = scanf(....);
	int y = scanf(....);
	matrix M;
	create_matrix(x,y,&M);

	for()
		for()

	return M;
}	


