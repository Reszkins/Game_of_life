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
#define COMP 3

int x=0;
ge_GIF *gif = NULL;

void error(int y){
	x=y;
	if(x==1)
		fprintf(stderr,"Błąd: Nieprawidłowe argumenty\n");

}

int check_error(){
	return x;
}

void close_gif()
{
	ge_close_gif(gif);
}

void write_world(matrix w, FILE *output, char *out){
	//printf("POROWNANIE: %d\n",strcmp(out,"stdout"));
	if(strcmp(out,"stdout")==0){
		for(int i=0; i < w.x; i++){
			for(int j=0; j < w.y; j++){
				fprintf(output,"%d ",w.v[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

char * generate_filename(int it, arguments cfg)
{
	int length = strlen(cfg.out) + strlen(cfg.format) + 3; 
	length += floor (log10 (abs (it))) + 1; //liczba cyfr iteracji
	char* filename = malloc(length * sizeof(char));
	strcpy(filename, cfg.out);
	strcat(filename, "_");
	sprintf(filename, "%d", it);
	strcat(filename, ".");
	strcat(filename, cfg.format);
}

void set_color_for_gif(uint8_t *pixels, int *index, int p)
{
	if(p) {
		pixels[(*index)++] = 1;
	}
	else {
		pixels[(*index)++] = 0;
	}
}

void set_color_for_image(uint8_t *pixels, int *index, int p)
{
	if(p) {
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

void save_png(uint8_t *pixels, int x, int y, char *filename)
{
	stbi_write_png(filename, x, y, COMP, pixels, x * CHANNEL_NUM);
}

void save_jpg(uint8_t *pixels, int x, int y, char *filename)
{
	 stbi_write_jpg(filename, x, y, COMP, pixels, 100);
}

void save_bmp(uint8_t *pixels, int x, int y, char *filename)
{
	 stbi_write_bmp(filename, x, y, COMP, pixels);
}

void save_gif(uint8_t *pixels, int x, int y, char *filename)
{

	if(gif == NULL){
		gif = ge_new_gif(filename, x, y, 
			(uint8_t []) {  /* palette */
				0x00, 0x00, 0x00, /* 0 -> black */
				0xFF, 0x00, 0x00, /* 1 -> red */
				0x00, 0xFF, 0x00, /* 2 -> green */
				0x00, 0x00, 0xFF, /* 3 -> blue */
        	}
			, 2, 0);
	}
	gif->frame = pixels;
	
	ge_add_frame(gif, 10);
}

uint8_t* set_pixels(matrix w, int scale, void (*f)(uint8_t *pixels, int *index, int p))
{
	int width = w.x * scale;
	int height = w.y * scale;

	uint8_t *pixels = malloc(width * height);

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

void save(matrix w, arguments cfg){	
	int scale = 10;
	int width = w.x * scale;
	int height = w.y * scale;
	char* filename = generate_filename(w.iteration, cfg);
	if(!strcmp(cfg.format, "png")) {
		uint8_t *pixels = set_pixels(w, scale, set_color_for_image);
		save_png(pixels, width, height, filename);
	} 
	else if(!strcmp(cfg.format, "jpg")) {
		uint8_t *pixels = set_pixels(w, scale, set_color_for_image);
		save_jpg(pixels, width, height, filename);
	}
	else if(!strcmp(cfg.format, "bmp")) {
		uint8_t *pixels = set_pixels(w, scale, set_color_for_image);
		save_bmp(pixels, width, height, filename);
	}
	else if(!strcmp(cfg.format, "gif")) {
		uint8_t *pixels = set_pixels(w, scale, set_color_for_gif);
		save_gif(pixels, width, height, filename);
		if(w.iteration == cfg.iterations - 1) close_gif();
	}
}


