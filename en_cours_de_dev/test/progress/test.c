#include <stdio.h>

int main()
{
	int i = 150;

	printf("first : %d\n", i);	// first : 150
	printf("second : %d\n", i + 1); // second : 151
	printf("thrid : %d\n", ++i);	// third : 150
	printf("fourth : %d\n", i);	// fourth : 151
}