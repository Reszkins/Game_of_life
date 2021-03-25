#include "output.h"
#include "matrix.h"
#include "input.h"

#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

#include "lib/gifenc.h"

#define CHANNEL_NUM 3

int x = 0;
ge_GIF* gif = NULL;

void display_help(){				// wyświetlenie pomocy
	printf("Usage: ./glife [arguments]\n");
	printf("Arguments:\n");
	printf("-h 							=> help\n");
	printf("-g (with one of:[glife, ant]				=> game\n");
	printf("-f (with filename or stdin) 				=> input file\n");
	printf("-o (with filename prefix) 				=> output file prefix\n");
	printf("-t (with one of:[gif, jpg, png, bmp, txt, stdout]) 	=> output file type\n");
	printf("-i (with integer number) 				=> number of iterations\n");
	printf("-r (with string eg. 36/23) 				=> rules\n");
}

void error(int y) {				// zgłoszenie błędu
	x = y;
	if (x == 1)
		fprintf(stderr, "Błąd: Nieprawidłowe argumenty\n");
	else if( x == 3) 
		fprintf(stderr, "Niepoprawny plik wejściowy dla mrówki, brak punktu początkowego\n");

}

int check_error() {				// zwrócenie błędu
	return x;
}

void close_gif()
{
	ge_close_gif(gif);
}

void write_world(matrix w, arguments cfg) {	// wypisanie świata, jeśli plik wyjściowy to stdout lub txt 
		for (int i = 0; i < w.x; i++) {
			for (int j = 0; j < w.y; j++) {
				fprintf(cfg.output, "%d ", w.v[i][j]);
			}
			fprintf(cfg.output, "\n");
		}
		fprintf(cfg.output, "\n");
}

char* generate_filename(int it, arguments cfg)	// stworzenie nazwy pliku wyjściowego
{
	char* filename;

	if(is_type(cfg, "gif") || is_type(cfg, "txt")){
		int length = strlen(cfg.out) + strlen(cfg.format) + 3;
		filename = malloc(length * sizeof(char));
		strcpy(filename, cfg.out);
		strcat(filename, ".");
		strcat(filename, cfg.format);
	}
	else{
		int length = it ? floor(log10(abs(it))) + 1 : 1; //liczba cyfr iteracji
		length += strlen(cfg.out) + strlen(cfg.format) + 3;
		filename = malloc(length * sizeof(char));
		strcpy(filename, cfg.out);
		strcat(filename, "_");
		int tmp = strlen(filename);
		snprintf(filename + tmp, length, "%d", it);
		strcat(filename, ".");
		strcat(filename, cfg.format);
	}
	return filename;
}

void set_color_for_gif(uint8_t* pixels, int* index, int p)	// ustalenie kolorów w gifie
{
	if(p == 2) {
		pixels[(*index)++] = 2;
	}
	else if (p) {
		pixels[(*index)++] = 1;
	}
	else {
		pixels[(*index)++] = 0;
	}
}

void set_color_for_image(uint8_t* pixels, int* index, int p)	// ustalenie kolorów w obrazie
{
	if (p == 2) {
		pixels[(*index)++] = 122;
		pixels[(*index)++] = 122;
		pixels[(*index)++] = 122;
	}
	else if (p) {
		pixels[(*index)++] = 255;
		pixels[(*index)++] = 255;
		pixels[(*index)++] = 255;
	}
	else {
		pixels[(*index)++] = 0;
		pixels[(*index)++] = 0;
		pixels[(*index)++] = 0;
	}
}

void save_png(uint8_t* pixels, int x, int y, char* filename)
{
	stbi_write_png(filename, x, y, 3, pixels, x * CHANNEL_NUM);
}

void save_jpg(uint8_t* pixels, int x, int y, char* filename)
{
	stbi_write_jpg(filename, x, y, 3, pixels, 100);
}

void save_bmp(uint8_t* pixels, int x, int y, char* filename)
{
	stbi_write_bmp(filename, x, y, 3, pixels);
}

void save_gif(uint8_t* pixels, int x, int y, char* filename)
{

	if (gif == NULL) {
		gif = ge_new_gif(filename, x, y,
			(uint8_t[]) {  /* palette */
				0x00, 0x00, 0x00, /* 0 -> black */
				0xFF, 0x00, 0x00, /* 1 -> red */
				0x00, 0xFF, 0x00, /* 2 -> green */
				0x00, 0x00, 0xFF, /* 3 -> blue */
		}
		, 2, 0);
	}
	memcpy(gif->frame, pixels, x*y);
	ge_add_frame(gif, 10);
}

uint8_t* set_pixels(matrix w, int scale, int comp, void (*f)(uint8_t *pixels, int *index, int p))	// stworzenie macierzy pixeli
{
	int width = w.x * scale;
	int height = w.y * scale;

	uint8_t *pixels = malloc(width * height * comp);

	int *index = malloc(sizeof *index);
	*index = 0;

	for(int i = 0; i < w.x; i++){
		for(int l = 0; l<scale; l++){
			for(int j = 0; j < w.y; j++){
				for(int k = 0; k<scale; k++){
					f(pixels, index, w.v[i][j]);
				}
			}
		}
	}

	free(index);

	return pixels;
}

void save(matrix w, arguments *args) {		// zapis świata
	uint8_t* pixels;
	arguments cfg = *args;	
	int scale = 10;
	int comp = 3;
	int width = w.x * scale;
	int height = w.y * scale;

	char* filename = generate_filename(w.iteration, cfg);

	if (is_type(cfg, "png")) {
		pixels = set_pixels(w, scale, comp, set_color_for_image);
		save_png(pixels, width, height, filename);
		free(pixels);
	}
	else if (is_type(cfg, "jpg")) {
		pixels = set_pixels(w, scale, comp, set_color_for_image);
		save_jpg(pixels, width, height, filename);
		free(pixels);
	}
	else if (is_type(cfg, "bmp")) {
		pixels = set_pixels(w, scale, comp, set_color_for_image);
		save_bmp(pixels, width, height, filename);
		free(pixels);
	}
	else if (is_type(cfg, "gif")) {
		comp = 1;
		pixels = set_pixels(w, scale, comp, set_color_for_gif);
		save_gif(pixels, width, height, filename);
		free(pixels);
		if (w.iteration == cfg.iterations - 1) close_gif();
	}
	else if (is_type(cfg, "txt") || is_type(cfg, "stdout")) {
		if(cfg.output == NULL) {
			args->output = is_type(cfg, "stdout") ? stdout : fopen(filename, "w"); 
			cfg = *args;
		}
		write_world(w, cfg);

		if (w.iteration == cfg.iterations - 1 && is_type(cfg, "txt")) 
		{
			fclose(cfg.output);
		}
	}
	
	free(filename);
}


