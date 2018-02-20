/*
 *  Name: Veerakumar Natarajan
 *  Degree: Masters in Computer Engineering
 *  College: North Carolina State University
 *
 */

/* Program to perform sobel operation on the given input gray image */

// Macro to define input and output file name
#define INPUT_FILE "kitten.pgm"
#define OUTPUT_FILE "output.pgm"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include <math.h>


int main() {
	PGMData input_img, output_img;
	int *output_gray, *input_gray, i, j, k, row, col, pixel_x, pixel_y;
	int g_x[3][3] = {{ 1,  0,  -1 }, { 2,  0,  -2 }, { 1,  0,  -1 }};
	int g_y[3][3] = {{ -1,  -2,  -1 }, { 0,  0,  0}, { 1,  2,  1 }};

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
	for(i = 1; i < row - 1; i++) {
		for(j = 1; j < col - 1; j++) {
			pixel_x = pixel_y = 0;

			pixel_x += (input_gray[(i - 1) * col + (j - 1)] * g_x[0][0]) + (input_gray[i * col + (j - 1)] * g_x[1][0]) + (input_gray[(i + 1) * col + (j - 1)] * g_x[2][0]) +
					   (input_gray[(i - 1) * col + (j + 1)] * g_x[0][2]) + (input_gray[i * col + (j + 1)] * g_x[1][2]) + (input_gray[(i + 1) * col + (j + 1)] * g_x[2][2]);
	
			pixel_y += (input_gray[(i - 1) * col + (j - 1)] * g_y[0][0]) + (input_gray[(i - 1) * col + j] * g_y[0][1]) + (input_gray[(i - 1) * col + (j + 1)] * g_x[0][2]) +
					   (input_gray[(i + 1) * col + (j - 1)] * g_y[2][0]) + (input_gray[(i + 1) * col + j] * g_y[2][1]) + (input_gray[(i + 1) * col + (j + 1)] * g_y[2][2]);

			output_gray[i * col + j] = sqrt(pow(pixel_x, 2) + pow(pixel_y, 2));
		}
	}

	output_img.row = row;
	output_img.col = col;
	output_img.max_gray = input_img.max_gray;

	// Creating output image after performing sobel operation
	writePGM(OUTPUT_FILE, &output_img);

	// Freeing up the memory
	free(output_gray);
	free(input_gray);

	return 0;
}
