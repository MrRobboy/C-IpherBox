#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 3 // Longueur maximale des combinaisons

// Fonction pour charger le charset depuis un fichier
char *loadCharset(const char *filename, int *charsetSize)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lire la première ligne du fichier
    char *charset = malloc(256); // Allouer un buffer pour le charset
    if (!charset)
    {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (fgets(charset, 256, file) == NULL)
    {
        perror("Erreur de lecture du fichier");
        free(charset);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    // Supprimer le saut de ligne éventuel
    charset[strcspn(charset, "\n")] = '\0';
    *charsetSize = strlen(charset);

    return charset;
}

void bruteForce(char *target, const char *charset, int charsetSize)
{
    char attempt[MAX_LENGTH + 1]; // Stocker une tentative
    attempt[MAX_LENGTH] = '\0';   // Terminer les chaînes avec '\0'

    for (int length = 1; length <= MAX_LENGTH; length++)
    {
        int indexes[length]; // Stocker les index actuels pour chaque longueur
        for (int i = 0; i < length; i++)
            indexes[i] = 0;

        while (1)
        {
            // Générer la chaîne pour les index actuels
            for (int i = 0; i < length; i++)
            {
                attempt[i] = charset[indexes[i]];
            }
            attempt[length] = '\0';

            printf("Tentative : %s\n", attempt);

            // Vérifier si la tentative correspond à la cible
            if (strcmp(attempt, target) == 0)
            {
                printf("Trouvé ! Le mot est : %s\n", attempt);
                return;
            }

            // Incrémenter les index
            int pos = length - 1;
            while (pos >= 0)
            {
                indexes[pos]++;
                if (indexes[pos] < charsetSize)
                    break;        // Pas de dépassement
                indexes[pos] = 0; // Réinitialiser et passer au caractère précédent
                pos--;
            }

            if (pos < 0)
                break; // Toutes les combinaisons sont générées
        }
    }

    printf("Mot non trouvé dans les combinaisons possibles.\n");
}

int main()
{
    char target[] = "abc"; // Mot secret

    // Charger le charset depuis un fichier
    int charsetSize;
    char *charset = loadCharset("charset.txt", &charsetSize);

    printf("Charset chargé : %s\n", charset);
    printf("Taille du charset : %d\n", charsetSize);

    // Lancer le brut force
    bruteForce(target, charset, charsetSize);

    // Libérer la mémoire allouée
    free(charset);

    return 0;
}
