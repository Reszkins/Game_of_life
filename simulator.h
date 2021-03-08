#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "matrix.h"

int neighbors_alive(matrix w, int x, int y);

void fix_matrix(matrix *w);

void next_generation(matrix *w);

#endif
