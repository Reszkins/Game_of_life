#include "matrix.h"

#include <stdlib.h>

void create_matrix(int x,int y,matrix *w) {
	w->x = x;
	w->y = y;
	w->iteration = 0;
	w->v = (int**)malloc(x * sizeof(int *));
	for(int i=0;i<x;i++)
		w->v[i] = (int*)malloc(y * sizeof(int));
}

void free_matrix(matrix *w) {
	for(int i=0;i<w->x;i++)
		free(w->v[i]);
	free(w->v);
}