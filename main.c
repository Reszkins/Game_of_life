#include "matrix.h"
#include "input.h"
#include "output.h"
#include "simulator.h"

#include <stdio.h>
#include <string.h>


int main(int argc,char **argv){

	arguments args;

	init_cfg(&args);				// ustalenie argumentów na wartości domyślne
	
	process_input(argc,argv,&args);			// przetworzenie argumentów wejściowych

	int e=check_error();				// sprawdzenie błędu
	if(e != 0) return e;

	if(args.help_wanted == 1){			// wyświetlanie pomocy, jeśli użytkownik o to prosi
	     	display_help();
		return 2;
	}
	
	matrix world = read_matrix(args.in);		// wczytanie świata początkowego z pliku

	for(int i=0; i < args.iterations; i++){		// tworzenie kolejnych iteracji

		save(world, &args);
		
		if(strcmp(args.game,"glife") == 0)	// w zależności od gry różne zasady
			next_generation(&world);
		else if(strcmp(args.game,"ant") == 0)
			ant_next_generation(&world);

	}

	free_matrix(&world);				// zwolnienie pamięci

	return 0;
}
