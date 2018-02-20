#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include <math.h>

int main() {
	PGMData input_img, output_img;
	int *output_gray, *input_gray, i, j, k, row, col, pixel_x, pixel_y;
	int g_x[3][3] = {{ 1,  0,  -1 }, { 2,  0,  -2 }, { 1,  0,  -1 }};
	int g_y[3][3] = {{ 1,  2,  1 }, { 0,  0,  0}, { -1,  -2,  -1 }};


	readPGM("kitten.pgm", &input_img);
	printf("size: x_res: %d, Y_res: %d, max_gray: %d\n", input_img.row, input_img.col, input_img.max_gray);

	row = input_img.row;
	col = input_img.col;

	output_img.data = malloc(row * col * sizeof(int));
	
	memset(output_img.data, 0x00, row * col* sizeof(int));

	output_gray = output_img.data;
	input_gray = input_img.data;	


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

	writePGM("output.pgm", &output_img);

	free(output_gray);
	free(input_gray);

	return 0;
}
