#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "matrix.h"
#include "input.h"

#include <stdio.h>
#include <stdint.h>

void save(matrix w, arguments *cfg);

void error(int x);

int check_error();

#endif
