#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int isDirectory(const char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}

int main()
{
	// char filename1[256], outputFilename1[256], key1[256];
	char *FicCmpEntree = NULL, *FicCmpSortie = NULL, *FicCmpSortieTemp = NULL, *Cle = NULL;
	short chiffrer = 0;

	printf("Entrez le fichier/dossier à compresser : ");
	scanf("%m[^\n]", &FicCmpEntree);
	if (FicCmpEntree == NULL)
	{
		printf("Erreur d'allocation dynamique FicCmpEntree : sortie du code !");
		exit(EXIT_FAILURE);
	}
	while (getchar() != '\n')
		;
	printf("Tentative d'ouverture du fichier : %s\n", FicCmpEntree);
	FILE *testFile = NULL;
	testFile = fopen(FicCmpEntree, "r");
	if (testFile == NULL)
	{
		printf("Erreur : le fichier '%s' n'existe pas.\n", FicCmpEntree);
		free(FicCmpEntree);
		FicCmpEntree = NULL;
		exit(EXIT_FAILURE);
	}
	fclose(testFile);
	printf("Fichier trouvé !\n");

reset_nom_sortie:
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
	if (strlen(FicCmpSortieTemp) >= 256)
	{
		printf("Nom du fichier de sortie trop grand ! Veuillez saisir un nom avec moins de 256 caractères.\n");
		free(FicCmpSortieTemp);
		FicCmpSortieTemp = NULL;
		goto reset_nom_sortie;
	}

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
