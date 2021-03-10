#include "output.h"
#include "matrix.h"

#include <stdio.h>
#include <string.h>


void write_world(matrix w, FILE *output, char *out){
	//printf("POROWNANIE: %d\n",strcmp(out,"stdout"));
	if(strcmp(out,"stdout")==0){
		for(int i=0; i < w.x; i++){
			for(int j=0; j < w.y; j++){
				fprintf(output,"%d ",w.v[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
