#include "simulator.h"
//#include "matrix.h"

#include <stdio.h>

//glife
int neighbors_alive(matrix w, int x, int y) {		// policzenie żywych sąsiadów
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

void fix_matrix(matrix *w) {				// przerobienie macierzy na macierz z wartościami tylko 1 lub 0
	for(int i=0; i < w->x; i++){
		for(int j=0; j < w->y; j++){
	      		if(w->v[i][j] == 3) w->v[i][j] = 0;
 			else if(w->v[i][j] == 2) w->v[i][j] = 1;
		}
	}		
}

void next_generation(matrix *w) {			// stworzenie nowej generacji świata
	for(int i=0; i < w->x; i++){	
		for(int j=0; j < w->y; j++){
			int alive = neighbors_alive(*w,i,j);
			if(w->v[i][j] == 0 && alive == 3) w->v[i][j] = 2;
			else if(w->v[i][j] == 1 && alive != 2 && alive != 3) w->v[i][j] = 3;
		}
	}
	w->iteration++;
	fix_matrix(w);
}

//ant
int ant = 0;
int ant_x = -1;
int ant_y = -1;
char direction = 'n';

void find_ant(matrix *w){			// znalezienie początkowej lokalizacji mrówki
	for(int i=0; i < w->x; i++){
		for(int j=0; j < w->y; j++){
			if(w->v[i][j] == 2){
				ant_x = i;
				ant_y = j;
				break;
			}
		}
	}
}

void ant_next_generation(matrix *w){		// stworzenie następnej generacji świata
	if(ant_x == -1 && ant_y == -1)
		find_ant(w);
	//printf("x: %d y: %d d: %c\n",ant_x,ant_y,direction);
	if(ant==0){
		w->v[ant_x][ant_y] = 1;
		if(direction == 'n'){
			if(ant_x-1 < 0) ant_x = w->x-1;
			else ant_x = ant_x - 1;
			direction = 'w';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}
		else if(direction == 's'){
			if(ant_x+1 == w->x) ant_x = 0;
			else ant_x = ant_x + 1;
			direction = 'e';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}	
		else if(direction == 'w'){
			if(ant_y-1 < 0) ant_y = w->y-1;
			else ant_y = ant_y - 1;
			direction = 's';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}
		else if(direction == 'e'){
			if(ant_y+1 == w->y) ant_y = 0;
			else ant_y = ant_y + 1;
			direction = 'n';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}	
	}
	else if(ant==1){
		w->v[ant_x][ant_y] = 0;
		if(direction == 'n'){
			if(ant_x+1 == w->x) ant_x = 0;
			else ant_x = ant_x + 1;
			direction = 'w';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}
		else if(direction == 's'){
			if(ant_x-1 < 0) ant_x = w->x-1;
			else ant_x = ant_x - 1;
			direction = 'e';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}	
		else if(direction == 'w'){
			if(ant_y+1 == w->y) ant_y = 0;
			else ant_y = ant_y + 1;
			direction = 's';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}
		else if(direction == 'e'){
			if(ant_y-1 < 0) ant_y = w->y-1;
			else ant_y = ant_y - 1;
			direction = 'n';
			if(w->v[ant_x][ant_y] == 0)
				ant = 0;
			else
				ant = 1;
			w->v[ant_x][ant_y] = 2;
		}
	}
	w->iteration++;
}