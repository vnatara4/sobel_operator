/*
 *	Name: Veerakumar Natarajan
 *	Degree: Masters in Computer Engineering
 *	College: North Carolina State University
 *
 */

// Macro which defines kernel matrix dimension (allowed dimensions: 3x3, 5x5, 7x7, 9x9)
#define N 3

// Macro to define input and output file name
#define INPUT_FILE "kitten.pgm"
#define OUTPUT_FILE "output_ks.pgm"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include <math.h>

// Header file which includes kernel matirx
#include "sobel.h"

int main() {
	PGMData input_img, output_img;
	int *output_gray, *input_gray, i, j, k, l, row, col, pixel_x, pixel_y;

	// Reading input image and storing that in an array
	readPGM(INPUT_FILE, &input_img);

	row = input_img.row;
	col = input_img.col;

	// Allocating memory for output image
	output_img.data = malloc(row * col * sizeof(int));
	
	if(output_img.data == NULL) {
		printf("failed to allocate memory for output image\n");
		return -1;
	}
	
	memset(output_img.data, 0x00, row * col* sizeof(int));

	output_gray = output_img.data;
	input_gray = input_img.data;	

	// Performing sobel operation on input image
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			pixel_x = pixel_y = 0;
			for(k = -N/2; k <= N/2; k++) {
				for(l = -N/2; l <= N/2; l++) {
					pixel_x += (((i + l) >= 0 && (j + k) >= 0) ? input_gray[(i + l) * col + (j + k)] : 0) * g_x[l + N/2][k + N/2];
				}
			}			

			output_gray[i * col + j] = sqrt(pow(pixel_x, 2) + pow(pixel_y, 2));
		}
	}

	output_img.row = row;
	output_img.col = col;
	output_img.max_gray = input_img.max_gray;

	// Creating output image after performing sobel operation
	writePGM(OUTPUT_FILE, &output_img);

	// Freing up the memory
	free(output_gray);
	free(input_gray);

	return 0;
}
