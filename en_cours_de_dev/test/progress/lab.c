#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Val_ASCII 256

int *FillTabHzChar(char *filename, int *frequence)
{
	FILE *fichier = NULL;
	fichier = fopen(filename, "r");
	if (fichier == NULL)
	{
		perror("Erreur ouverture fichier");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Max_Val_ASCII; i++)
		frequence[i] = 0;

	char c = 0;
	while ((c = fgetc(fichier)) != EOF)
		frequence[(unsigned char)c]++;

	fclose(fichier);
}

void ShowHz(int *frequence)
{
	for (unsigned int i = 0; i < Max_Val_ASCII; i++)
	{
		if (frequence[i] > 0)
			printf("Caractère '%c' (%u) : %d fois\n", i, i, frequence[i]);
	}
}

int main()
{
	int frequence[Max_Val_ASCII];
	FillTabHzChar("test.txt", frequence);
	ShowHz(frequence);
	return 0;
}