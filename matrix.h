#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct{
	int x;
	int y;
	int **v;
} matrix;

void create_matrix(int x, int y, matrix *w);

#endif
