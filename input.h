#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>

typedef struct{
	int help_wanted;
	int iterations;
	char in[260];
	//FILE *input;
	char out[260];
	FILE *output;
	char format[10];
	char game[50];
} arguments;

void init_cfg(arguments *args);

void display_help();

void process_input(int argc, char **argv, arguments *args);

int is_type(arguments cfg, const char* type);

matrix read_matrix(char *in);

#endif
