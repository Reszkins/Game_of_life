#include "simulator.h"
#include "matrix.h"

#include <stdio.h>

int main(){
	matrix q;
	create_matrix(10,10,&q);	

	for(int i=0;i<q.x;++i){
		for(int j=0;j<q.y;j++)
			q.v[i][j] = 0;
	}

	q.v[3][3] = 1;
	q.v[3][4] = 1;
	q.v[3][5] = 1;
	q.v[4][3] = 1;
	q.v[5][4] = 1;

	for(int k=0;k<10;k++){
		
		for(int i=0;i<q.x;++i){
			for(int j=0;j<q.y;++j){
				printf("%d ",q.v[i][j]);
			}
			printf("\n");
		}
		
		printf("\n");
		next_generation(&q);
	}

	return 0;
}
