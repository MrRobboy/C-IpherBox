#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	// char filename1[256], outputFilename1[256], key1[256];
	char *FicCmpEntree = NULL, *FicCmpSortie = NULL, *FicCmpSortieTemp = NULL, *Cle = NULL;
	short chiffrer = 0;

	printf("Entrez le fichier à compresser : ");
	scanf("%m[^\n]", &FicCmpEntree);
	if (FicCmpEntree == NULL)
	{
		printf("Erreur d'allocation dynamique FicCmpEntree : sortie du code !");
		exit(EXIT_FAILURE);
	}
	while (getchar() != '\n')
		;
	printf("\n\nNom du fichier compressé (ex: output.huff) : ");
	scanf("%m[^\n]", &FicCmpSortieTemp);
	if (FicCmpSortieTemp == NULL)
	{
		printf("Erreur d'allocation dynamique FicCmpSortieTemp : sortie du code !");
		free(FicCmpEntree);
		FicCmpEntree = NULL;
		exit(EXIT_FAILURE);
	}
	while (getchar() != '\n')
		;
	printf("Taille de FicCmpSortieTemp : %lld\n", strlen(FicCmpSortieTemp));

	if (strstr(FicCmpSortieTemp, ".huff") == NULL)
	{
		FicCmpSortie = malloc(strlen(FicCmpSortieTemp) + 5);
		sprintf(FicCmpSortie, "%s.huff", FicCmpSortieTemp);
		printf("Nom du fichier de sortie : %s\n", FicCmpSortie);
	}

	printf("\n\nVoulez-vous chiffrer le fichier ? (1 = Oui, 0 = Non) : ");
	scanf("%hd", &chiffrer);
	while (getchar() != '\n')
		;
	if (chiffrer)
	{
		printf("Entrez une clé de chiffrement : ");
		scanf("%m[^\n]", &Cle);
		if (Cle == NULL)
		{
			printf("Erreur d'allocation dynamique Cle : sortie du code !");
			free(FicCmpEntree);
			FicCmpEntree = NULL;
			free(FicCmpSortie);
			FicCmpSortie = NULL;
			free(FicCmpSortieTemp);
			FicCmpSortieTemp = NULL;
			exit(EXIT_FAILURE);
		}

		while (getchar() != '\n')
			;
	}

	// Appel de la compression ici

	printf("\n\nValeurs entrées : \nFicCmpEntree = '%s'\nFicCmpSortie = '%s'\nchiffrer = %d\n", FicCmpEntree, FicCmpSortie, chiffrer);
	if (Cle != NULL)
		printf("Clé de chiffrement : %s\n", Cle);

	printf("\n\nFichier compressé avec succès sous : %s\n", FicCmpSortie);

	exit(EXIT_SUCCESS);
}
