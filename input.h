#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>

typedef struct{
	int help_wanted;
	int iterations;
	char *in;
	FILE *input;
	char *out;
	FILE *output;
} arguments;

void display_help();

void process_input(int argc, char **argv, arguments *args);

matrix read_matrix(FILE *in);

#endif
