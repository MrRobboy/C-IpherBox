#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Pour Windows uniquement
#include <unistd.h>  // Pour Linux/Mac (remplacer par Sleep() sur Windows)
#include "hashing.h"

#define MAX_SIZE 4
#define MAX_TRIES 1000000
#define CHARSET_FILE "charset.txt"
#define TARGET_FILE "target.txt"
#define WORDLIST_FILE "wordlist.txt"
#define THREAD_COUNT 4

char *charset;
int charsetSize = 0;
char target_hash[65];
int found = 0;

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    printf("\033[H\033[J"); // Linux/Mac
#endif
}

void printMenu()
{
    clearScreen();
    printf("\n======================================\n");
    printf("|        OUTIL BRUTE FORCE           |\n");
    printf("======================================\n");
    printf("| [1]  Brut Force Classique         |\n");
    printf("| [2]  Brut Force Dictionnaire      |\n");
    printf("| [3]  Brut Force Hachage (MD5, SHA-1) |\n");
    printf("| [4]  Quitter                      |\n");
    printf("======================================\n");
    printf("Choisissez une option (1-4) : ");
}

char *loadCharset(const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier charset");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(256);
    if (!buffer)
    {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer, 256, file) == NULL)
    {
        perror("Erreur de lecture du fichier");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    buffer[strcspn(buffer, "\n")] = '\0';
    *size = strlen(buffer);
    return buffer;
}

void bruteForceClassic()
{
    char guess[MAX_SIZE + 1] = {0};
    int guessc[MAX_SIZE] = {0};
    int tries = 0;

    while (tries++ < MAX_TRIES)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            guess[i] = charset[guessc[i]];
        }
        guess[MAX_SIZE] = '\0';

        printf("\rTentative %d: %s", tries, guess);
        fflush(stdout);

        if (strcmp(guess, "abc") == 0) // Simule un mot cible
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, guess);
            return;
        }

        int i = 0;
        while (i < MAX_SIZE)
        {
            guessc[i]++;
            if (guessc[i] < charsetSize)
                break;
            guessc[i] = 0;
            i++;
        }

        if (i == MAX_SIZE)
            break;
    }

    printf("\nMot non trouvé après %d tentatives.\n", MAX_TRIES);
}

void bruteForceWordlist()
{
    FILE *file = fopen(WORDLIST_FILE, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier wordlist");
        return;
    }

    char line[256];
    int tries = 0;

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        tries++;

        printf("\rTentative %d: %s", tries, line);
        fflush(stdout);

        if (strcmp(line, "password") == 0) // Simule un mot cible
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, line);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nMot non trouvé dans la wordlist.\n");
}

void bruteForceHash()
{
    int choice;
    printf("\nSélectionnez le type de hachage :\n");
    printf("[1] MD5\n");
    printf("[2] SHA-1\n");
    printf("Votre choix : ");
    scanf("%d", &choice);
    getchar(); // Évite le problème de buffer avec `scanf`

    FILE *file = fopen(TARGET_FILE, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier hash");
        return;
    }
    fgets(target_hash, sizeof(target_hash), file);
    target_hash[strcspn(target_hash, "\n")] = '\0';
    fclose(file);

    char guess[MAX_SIZE + 1] = {0};
    char computed_hash[65];
    int guessc[MAX_SIZE] = {0};
    int tries = 0;

    while (tries++ < MAX_TRIES)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            guess[i] = charset[guessc[i]];
        }
        guess[MAX_SIZE] = '\0';

        switch (choice)
        {
        case 1:
            computeMD5(guess, computed_hash);
            break;
        case 2:
            computeSHA1(guess, computed_hash);
            break;
        default:
            printf("\nOption invalide !\n");
            return;
        }

        printf("\rTentative %d: %s", tries, guess);
        fflush(stdout);

        if (strcmp(computed_hash, target_hash) == 0)
        {
            printf("\nMot trouvé après %d tentatives : %s\n", tries, guess);
            return;
        }

        int i = 0;
        while (i < MAX_SIZE)
        {
            guessc[i]++;
            if (guessc[i] < charsetSize)
                break;
            guessc[i] = 0;
            i++;
        }

        if (i == MAX_SIZE)
            break;
    }

    printf("\nHachage non trouvé après %d tentatives.\n", MAX_TRIES);
}

int main()
{
    charset = loadCharset(CHARSET_FILE, &charsetSize);
    int choice;

    while (1)
    {
        printMenu();
        printf(">> ");
        scanf("%d", &choice);
        getchar(); // Évite les problèmes de buffer avec `scanf`

        switch (choice)
        {
        case 1:
            bruteForceClassic();
            break;
        case 2:
            bruteForceWordlist();
            break;
        case 3:
            bruteForceHash();
            break;
        case 4:
            printf("Fin du programme.\n");
            free(charset);
            return 0;
        default:
            printf("Option invalide !\n");
        }

        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }
}
