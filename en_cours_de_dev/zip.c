#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <limits.h>

// int compress(FILE *fichier, char *m)
// {
// }

int main()
{
	printf("   ______       ____        __                 ____              \n");
	printf("  / ____/      /  _/____   / /_   ___   _____ / __ ) ____   _  __\n");
	printf(" / /   ______  / / / __ \\ / __ \\ / _ \\ / ___// __  |/ __ \\ | |/_/\n");
	printf("/ /___/_____/_/ / / /_/ // / / //  __// /   / /_/ // /_/ /_>  <  \n");
	printf("\\____/      /___// .___//_/ /_/ \\___//_/   /_____/ \\____//_/|_|  \n");
	printf("                /_/                                              \n\n");

	printf("===\n1 - Compresser un fichier (tar)\n2 - Décompresser un fichier (tar)\n===\n>>>");
	char *reponse;
	char *cmd;
	scanf("%m[^\n]", &reponse);

	if (strcmp(reponse, "1") == 0)
	{
		fgetc(stdin);
		char *fic_a_zip;
		char *nom_sortie_temp;
		char *nom_sortie;

		printf("Fichier à compresser : ");
		scanf("%m[^\n]", &fic_a_zip);
		printf("'%s'\n", fic_a_zip);
		fgetc(stdin);

		printf("Nom du fichier de sortie : ");
		scanf("%m[^\n]", &nom_sortie_temp);
		printf("'%s'\n", nom_sortie_temp);
		fgetc(stdin);

		if (strstr(nom_sortie_temp, ".tar") == NULL)
		{
			sprintf(nom_sortie, "%s.tar", nom_sortie_temp);
			printf("%s\n", nom_sortie);
		}
		else
		{
			sprintf(nom_sortie, "%s", nom_sortie_temp);
			printf("%s\n", nom_sortie);
		}

		sprintf(cmd, "tar -cf %s %s", nom_sortie, fic_a_zip);
		system(cmd);
		free(fic_a_zip);
		free(nom_sortie);
		free(nom_sortie_temp);
		free(reponse);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(reponse, "2") == 0)
	{
		char *fic_a_dezip;
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");
			free(reponse);
			exit(EXIT_FAILURE);
		}
		printf("\n\nCurrent working dir: %s\n\n\n", cwd);
	}
	else
	{
		printf("Erreur de format saisi.\nChoisissez entre 1 et 2 la prochaine fois !!! Je ne vous fais plus confiance pour continuer :'(");
		exit(EXIT_FAILURE);
	}
}