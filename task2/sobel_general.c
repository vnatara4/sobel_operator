
#define N 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include <math.h>
#include "sobel.h"

int main() {
	PGMData input_img, output_img;
	int *output_gray, *input_gray, i, j, k, l, row, col, pixel_x, pixel_y;

	readPGM("kitten.pgm", &input_img);
	printf("size: x_res: %d, Y_res: %d, max_gray: %d\n", input_img.row, input_img.col, input_img.max_gray);

	row = input_img.row;
	col = input_img.col;

	output_img.data = malloc(row * col * sizeof(int));
	
	memset(output_img.data, 0x00, row * col* sizeof(int));

	output_gray = output_img.data;
	input_gray = input_img.data;	

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

	writePGM("output_gen.pgm", &output_img);

	free(output_gray);
	free(input_gray);

	return 0;
}
