#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	printf("   ______       ____        __                 ____              \n");
	printf("  / ____/      /  _/____   / /_   ___   _____ / __ ) ____   _  __\n");
	printf(" / /   ______  / / / __ \\ / __ \\ / _ \\ / ___// __  |/ __ \\ | |/_/\n");
	printf("/ /___/_____/_/ / / /_/ // / / //  __// /   / /_/ // /_/ /_>  <  \n");
	printf("\\____/      /___// .___//_/ /_/ \\___//_/   /_____/ \\____//_/|_|  \n");
	printf("                /_/                                              \n\n");

	printf("========================\n1 - Compresser un fichier (tar)\n2 - Décompresser un fichier (tar)\n========================\n>>> ");
	char *reponse = NULL;
	scanf("%m[^\n]", &reponse);
	fgetc(stdin);

	if (strcmp(reponse, "1") == 0)
	{
		char *cmd = NULL;
		char *fic_a_zip = NULL;
		char *nom_sortie_temp = NULL;
		char *nom_sortie = NULL;

		printf("Fichier à compresser : ");
		scanf("%m[^\n]", &fic_a_zip);
		fgetc(stdin);

		printf("Nom du fichier de sortie : ");
		scanf("%m[^\n]", &nom_sortie_temp);
		fgetc(stdin);

		if (strstr(nom_sortie_temp, ".tar") == NULL)
		{
			nom_sortie = malloc(1024);
			if (nom_sortie == NULL)
			{
				perror("Erreur d'allocation de mémoire");
				exit(EXIT_FAILURE);
			}
			sprintf(nom_sortie, "%s.tar", nom_sortie_temp);
			printf("%s\n", nom_sortie);
		}
		else
		{
			nom_sortie = malloc(1024);
			if (nom_sortie == NULL)
			{
				perror("Erreur d'allocation de mémoire");
				exit(EXIT_FAILURE);
			}
			sprintf(nom_sortie, "%s", nom_sortie_temp);
			printf("%s\n", nom_sortie);
		}

		cmd = malloc(1024);
		if (cmd == NULL)
		{
			perror("Erreur d'allocation de mémoire");
			exit(EXIT_FAILURE);
		}
		sprintf(cmd, "tar -cf %s %s", nom_sortie, fic_a_zip);
		printf("Execution de la commande : %s", cmd);
		system(cmd);

		free(nom_sortie);
		nom_sortie = NULL;
		free(nom_sortie_temp);
		nom_sortie_temp = NULL;
		free(fic_a_zip);
		fic_a_zip = NULL;
		free(cmd);
		cmd = NULL;
		free(reponse);
		reponse = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(reponse, "2") == 0)
	{
		char *cmd = NULL;
#ifdef _WIN32
		printf("\n Dossier actuel : ");
		system("pwd");
		printf("\nÉléments dans ce dossier :\n");
		system("ls");
#elif __linux__
		printf("\n Dossier actuel : ");
		system("pwd");
		printf("\n\nÉléments dans ce dossier :\n");
		system("ls");
#else
		printf("Unknown operating system\n");
		exit(EXIT_FAILURE);
#endif

		char *fic_a_dezip = NULL;
		printf("Fichier à décompresser : ");
		scanf("%m[^\n]", &fic_a_dezip);
		fgetc(stdin);
		printf("fic a dezip : '%s'\n", fic_a_dezip);

		cmd = malloc(1024);
		if (cmd == NULL)
		{
			perror("Erreur d'allocation de mémoire");
			free(reponse);
			reponse = NULL;
			free(fic_a_dezip);
			fic_a_dezip = NULL;
			exit(EXIT_FAILURE);
		}
		sprintf(cmd, "tar -xf %s", fic_a_dezip);
		printf("%s", cmd);
		printf("\nExecution de la commande suivante : %s\n", cmd);
		system(cmd);

		free(fic_a_dezip);
		fic_a_dezip = NULL;
		free(cmd);
		cmd = NULL;

		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Erreur de format saisi.\nChoisissez entre 1 et 2 la prochaine fois !!! Je ne vous fais plus confiance pour continuer :'(");
		free(reponse);
		reponse = NULL;
		exit(EXIT_FAILURE);
	}
}