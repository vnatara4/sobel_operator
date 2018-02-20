/******************************************************************************

	Name: Veerakumar Natarajan
	Degree: Masters of Science
	Major: Computer Engineering
	College: North Carolina State University
	E-mail: vnatara4@ncsu.edu
	Phone: +1 9842188035 

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_STR	3
#define MAX_LEN	13

/* Function to print the list of strings */
void print_list(char list[][MAX_LEN]) {
	int i;
	for(i = 0; i < NUM_STR; i++)
		printf("%s\n", list[i]);	
}

/* Function to sort the list of strings in ascending order */
void ascend(char list[][MAX_LEN]) {
	char tmp[MAX_LEN];
	int i, j;
	for(i = 0; i < NUM_STR; i++) {
		for(j = 0; j < NUM_STR - i - 1; j++) {
			if(strcmp(list[j], list[j+1]) > 0) {
				strcpy(tmp, list[j+1]);
				strcpy(list[j+1], list[j]);
				strcpy(list[j], tmp);
			}
		}
	}	
}

/* Function to sort the list of strings in ascending order */
void descend(char list[][MAX_LEN]) {
	char tmp[MAX_LEN];
	int i, j;
	for(i = 0; i < NUM_STR; i++) {
		for(j = 0; j < NUM_STR - i - 1; j++) {
			if(strcmp(list[j], list[j+1]) < 0) {
				strcpy(tmp, list[j+1]);
				strcpy(list[j+1], list[j]);
				strcpy(list[j], tmp);
			}
		}
	}	
}

/* Function to return the position of shortest string in the list */
int shortest(char list[][MAX_LEN]) {
	int str_len[NUM_STR], i, pos;

	for(i = 0; i < NUM_STR; i++)
		str_len[i] = strlen(list[i]);

	pos = (str_len[0] < str_len[1]) ? 0 : 1;
	return ((str_len[pos] < str_len[2]) ? pos : 2);
}


/* Function to perform corresponding operation based on input */
void list_op(char list[][MAX_LEN], int a) {
	switch(a) {
		case 0:
			ascend(list);
			print_list(list);
			break;
		case 1:
			descend(list);
			print_list(list);
			break;
		case 2:
			printf("%s\n",list[shortest(list)]);
			break;
		default:
			printf("Second integer should be either 0, 1 or 2\n");
	}
}


int main() {
	char list1[NUM_STR][MAX_LEN] = {"String 1", "String 22", "String 333"};
	char list2[NUM_STR][MAX_LEN] = {"String red", "String green", "String blue"};
	char list3[NUM_STR][MAX_LEN] = {"String small", "String med", "String large"};	
	char a[2], b[2];
	int first_int, second_int, i;
	char tmp;

	printf("Enter the first integer(0, 1, 2):\n");
	
	/* Verifying given input is valid or not */
	if(scanf("%c%c", &a[0], &tmp) != 2 || tmp != '\n') {
		printf("Invalid input\n");
		return -1;
	}

	printf("Enter the second integer(0, 1, 2):\n");
	if(scanf("%c%c", &b[0], &tmp) != 2 || tmp != '\n') {
		printf("Invalid input\n");
		return -1;
	}

	/* Verifying input is an integer or not */
	if(!isdigit(a[0]) || !isdigit(b[0])) {
		printf("Input should be an integer\n");
		return -1;
	}

	a[1] = '\0';
	b[1] = '\0';

	first_int = atoi(a);
	second_int = atoi(b);

	/* Slecting list of strings based on input */
	switch(first_int) {
		case 0:
			list_op(list1, second_int);
			break;
		case 1:
			list_op(list2, second_int);
			break;
		case 2:
			list_op(list3, second_int);
			break;
		default:
			printf("First integer should be either 0, 1 or 2\n");
	}

	return 0;
}
