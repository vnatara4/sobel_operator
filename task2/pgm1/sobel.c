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

#define OPT
#define OPT2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include <math.h>
#include <time.h>
#include "sqrt_lookup.h"

int main() {
	PGMData input_img, output_img;
	int *output_gray, *input_gray, i, j, k, row, col, pixel_x, pixel_y;
	int g_x[3][3] = {{ 1,  0,  -1 }, { 2,  0,  -2 }, { 1,  0,  -1 }};
	int g_y[3][3] = {{ -1,  -2,  -1 }, { 0,  0,  0}, { 1,  2,  1 }};
	int tmp_x[2], **tmp_y, val;
	clock_t start, end;
	double cpu_time_used;

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

	tmp_y = (int **)malloc(2 * sizeof(int *));
	for(i = 0; i < 2; i++) {
		tmp_y[i] = (int *)malloc(col * sizeof(int));
	}	

	memset(output_img.data, 0x00, row * col* sizeof(int));

	output_gray = output_img.data;
	input_gray = input_img.data;	

	start = clock();

	for(j = 1; j < col - 1; j++) {
		tmp_y[1][j] = -(input_gray[(j - 1)]) + (input_gray[j] * -2) - (input_gray[(j + 1)]);
		tmp_y[0][j] = -(input_gray[col + (j - 1)]) + (input_gray[col + j] * -2) - (input_gray[col + (j + 1)]);
	}

	// Performing sobel operation on input image
	for(i = 1; i < row - 1; i++) {

#ifdef OPT
#ifdef OPT1
		tmp_x[1] = (input_gray[(i - 1)] * g_x[0][0]) + (input_gray[i * col] * g_x[1][0]) + (input_gray[(i + 1) * col] * g_x[2][0]);
		tmp_x[0] = (input_gray[(i - 1) * col + 2] * g_x[0][2]) + (input_gray[i * col + 2] * g_x[1][2]) + (input_gray[(i + 1) * col + 2] * g_x[2][2]);
#endif

#ifdef OPT2
		tmp_x[1] = (input_gray[(i - 1)]) + (input_gray[i * col] * 2) + (input_gray[(i + 1) * col]);
		tmp_x[0] = -(input_gray[(i - 1) * col + 2]) + (input_gray[i * col + 2] * -2) - (input_gray[(i + 1) * col + 2]);					
#endif
#endif
		for(j = 1; j < col - 1; j++) {
			pixel_x = pixel_y = 0;

#ifdef OPT
#ifdef OPT1
			pixel_x = -tmp_x[(j % 2)];
			tmp_x[(j % 2)] = (input_gray[(i - 1) * col + (j + 1)] * g_x[0][2]) + (input_gray[i * col + (j + 1)] * g_x[1][2]) + (input_gray[(i + 1) * col + (j + 1)] * g_x[2][2]);
			pixel_x += tmp_x[(j % 2)];
			
			pixel_y = -tmp_y[(i % 2)][j];
			tmp_y[(i % 2)][j] = (input_gray[(i + 1) * col + (j - 1)] * g_y[2][0]) + (input_gray[(i + 1) * col + j] * g_y[2][1]) + (input_gray[(i + 1) * col + (j + 1)] * g_y[2][2]); 
			pixel_y += tmp_y[(i % 2)][j];
#endif
#ifdef OPT2
		pixel_x = -tmp_x[(j % 2)];
		tmp_x[(j % 2)] = -(input_gray[(i - 1) * col + (j + 1)]) + (input_gray[i * col + (j + 1)] * -2) - (input_gray[(i + 1) * col + (j + 1)]);
		pixel_x += tmp_x[(j % 2)];

		pixel_y = -tmp_y[(i % 2)][j];
		tmp_y[(i % 2)][j] = (input_gray[(i + 1) * col + (j - 1)]) + (input_gray[(i + 1) * col + j] * 2) + (input_gray[(i + 1) * col + (j + 1)]); 
		pixel_y += tmp_y[(i % 2)][j];

#endif

#else
			pixel_x += (input_gray[(i - 1) * col + (j - 1)] * g_x[0][0]) + (input_gray[i * col + (j - 1)] * g_x[1][0]) + (input_gray[(i + 1) * col + (j - 1)] * g_x[2][0]) +
					   (input_gray[(i - 1) * col + (j + 1)] * g_x[0][2]) + (input_gray[i * col + (j + 1)] * g_x[1][2]) + (input_gray[(i + 1) * col + (j + 1)] * g_x[2][2]);
	

			pixel_y += (input_gray[(i - 1) * col + (j - 1)] * g_y[0][0]) + (input_gray[(i - 1) * col + j] * g_y[0][1]) + (input_gray[(i - 1) * col + (j + 1)] * g_x[0][2]) +
					   (input_gray[(i + 1) * col + (j - 1)] * g_y[2][0]) + (input_gray[(i + 1) * col + j] * g_y[2][1]) + (input_gray[(i + 1) * col + (j + 1)] * g_y[2][2]);
#endif

#ifdef OPT
#if 0
			val = (pixel_x * pixel_x) + (pixel_y * pixel_y);
			if (val > 65026) {
				output_gray[i * col + j] = 255;
			} else {
				output_gray[i * col + j] = SQRT[val];
			}
#else
			output_gray[i * col + j] = abs(pixel_x) + abs(pixel_y);
#endif
#else
			output_gray[i * col + j] = sqrt(pixel_x * pixel_x + pixel_y * pixel_y);
#endif
		}
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Time used: %f\n", cpu_time_used);
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
