#include "simulator.h"
//#include "matrix.h"

#include <stdio.h>

int neighbors_alive(matrix w, int x, int y) {
	int alive = 0;
	for(int i = x-1; i < x+2 && i < w.x; i++){
		for(int j = y-1; j < y+2 && j < w.y; j++){
			if(i >= 0 && j >= 0){
				if(i == x && j == y);
				else if(w.v[i][j] == 1 || w.v[i][j] == 3) alive++;
			}
		}
	}
	return alive;
}

void fix_matrix(matrix *w) {
	for(int i=0; i < w->x; i++){
		for(int j=0; j < w->y; j++){
	      		if(w->v[i][j] == 3) w->v[i][j] = 0;
 			else if(w->v[i][j] == 2) w->v[i][j] = 1;
		}
	}		
}

void next_generation(matrix *w) {
	for(int i=0; i < w->x; i++){
		for(int j=0; j < w->y; j++){
			int alive = neighbors_alive(*w,i,j);
			if(w->v[i][j] == 0 && alive == 3) w->v[i][j] = 2;
			else if(w->v[i][j] == 1 && alive != 2 && alive != 3) w->v[i][j] = 3;
		}
	}
	fix_matrix(w);
}
