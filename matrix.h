#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct{
	int x;
	int y;
	int **v;
	int iteration;
} matrix;

void create_matrix(int x, int y, matrix *w);
void free_matrix(matrix *w);
#endif
