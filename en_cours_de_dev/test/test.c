#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	// char commande[256];
	// strcpy(commande, "dir /w /aa");
	// system(commande);

	const char *original = "Original String";
	char *copy = strdup(original);

	if (copy != NULL)
	{
		printf("Original: %s\n", original);
		printf("Copy: %s\n", copy);
		free(copy); // Free the allocated memory
	}
	else
	{
		printf("Failed to allocate memory for the copy.\n");
	}

	return 0;
}