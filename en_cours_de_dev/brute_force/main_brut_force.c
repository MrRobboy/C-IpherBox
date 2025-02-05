#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

void bruteForceClassic(const char *charset, int charsetSize, const char *target)
{
    int length = 1;
    int tries = 0;
    int indices[MAX_SIZE] = {0};
    char guess[MAX_SIZE + 1] = {0};

    printf("\nDémarrage du brute-force...\n");

    while (length <= MAX_SIZE)
    {
        while (1)
        {
            for (int i = 0; i < length; i++)
            {
                guess[i] = charset[indices[i]];
            }
            guess[length] = '\0';

            printf("\rTentative %d: %s", tries, guess);
            fflush(stdout);

            if (strcmp(guess, target) == 0)
            {
                printf("\nMot trouvé après %d tentatives : %s\n", tries, guess);
                return;
            }

            tries++;

            int i = 0;
            while (i < length)
            {
                indices[i]++;
                if (indices[i] < charsetSize)
                    break;
                indices[i] = 0;
                i++;
            }

            if (i == length)
                break;
        }
        length++;
        memset(indices, 0, sizeof(indices));
    }

    printf("\nMot non trouvé après %d tentatives.\n", tries);
}

void bruteForceDictionary(const char *target, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier dictionnaire");
        return;
    }

    char line[256];
    int tries = 0;

    printf("\nDémarrage du brute-force par dictionnaire...\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        tries++;

        printf("\rTentative %d: %s", tries, line);
        fflush(stdout);

        if (strcmp(line, target) == 0)
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, line);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nMot non trouvé dans la wordlist.\n");
}

void bruteForceMD5Dictionary(const char *target, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier wordlist MD5");
        return;
    }

    char line[256];
    char computed_hash[65];
    int tries = 0;

    printf("\nDémarrage du brute-force MD5 par dictionnaire...\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        tries++;

        computeMD5(line, computed_hash);
        printf("\rTentative %d: %s (Hash: %s) -> Cible: %s", tries, line, computed_hash, target);
        fflush(stdout);

        if (strcmp(computed_hash, target) == 0)
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, line);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nMot non trouvé dans la wordlist MD5.\n");
}

void bruteForceSHA1Dictionary(const char *target, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier wordlist SHA1");
        return;
    }

    char line[256];
    char computed_hash[65];
    int tries = 0;

    printf("\nDémarrage du brute-force SHA-1 par dictionnaire...\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        tries++;

        computeSHA1(line, computed_hash);
        printf("\rTentative %d: %s (Hash: %s) -> Cible: %s", tries, line, computed_hash, target);
        fflush(stdout);

        if (strcmp(computed_hash, target) == 0)
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, line);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nMot non trouvé dans la wordlist SHA1.\n");
}

void printMenu()
{
    printf("\n======================================\n");
    printf("|        OUTIL BRUTE FORCE           |\n");
    printf("======================================\n");
    printf("| [1]  Brut Force Classique         |\n");
    printf("| [2]  Brut Force Dictionnaire      |\n");
    printf("| [3]  Brut Force MD5 (Dictionnaire)|\n");
    printf("| [4]  Brut Force SHA-1 (Dictionnaire) |\n");
    printf("| [5]  Quitter                      |\n");
    printf("======================================\n");
    printf("Choisissez une option (1-5) : ");
}

int main()
{
    char charset[] = "abcdefghijklmnopqrstuvwxyz";
    int charsetSize = strlen(charset);
    char target[65];

    FILE *file = fopen(TARGET_FILE, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier target.txt");
        return EXIT_FAILURE;
    }
    fgets(target, sizeof(target), file);
    fclose(file);
    target[strcspn(target, "\n")] = '\0';

    int choice;
    while (1)
    {
        printMenu();
        printf(">> ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            bruteForceClassic(charset, charsetSize, target);
            break;
        case 2:
            bruteForceDictionary(target, WORDLIST_FILE);
            break;
        case 3:
            bruteForceMD5Dictionary(target, "wordlist_md5.txt");
            break;
        case 4:
            bruteForceSHA1Dictionary(target, "wordlist_sha1.txt");
            break;
        case 5:
            printf("Fin du programme.\n");
            return EXIT_SUCCESS;
        default:
            printf("Option invalide !\n");
        }

        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }

    return EXIT_SUCCESS;
}
