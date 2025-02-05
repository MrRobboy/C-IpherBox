#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define Max_Val_ASCII 256

typedef struct Noeud Noeud;
struct Noeud
{
	char caractere;
	int frequence;
	struct Noeud *gauche, *droite;
};

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
	return frequence;
}

void ShowHz(int *frequence)
{
	for (unsigned int i = 0; i < Max_Val_ASCII; i++)
	{
		if (frequence[i] > 0)
			printf("Caractère '%c' (%u) : %d fois\n", i, i, frequence[i]);
	}
}

Noeud *creerNoeud(char caractere, int frequence, Noeud *gauche, Noeud *droite)
{
	Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
	if (!noeud)
	{
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	noeud->caractere = caractere;
	noeud->frequence = frequence;
	noeud->gauche = gauche;
	noeud->droite = droite;
	return noeud;
}

typedef struct Arbre Arbre;
struct Arbre
{
	int taille;
	int capacite;
	Noeud **tableau;
};

Arbre *creerArbre(int capacite)
{
	Arbre *heap = (Arbre *)malloc(sizeof(Arbre));
	if (!heap)
	{
		perror("Erreur d'allocation");
		exit(EXIT_FAILURE);
	}
	heap->taille = 0;
	heap->capacite = capacite;
	heap->tableau = (Noeud **)malloc(capacite * sizeof(Noeud *));
	return heap;
}

void heapifyDown(Arbre *heap, int i);
void heapifyUp(Arbre *heap, int i);

Noeud *extraireMin(Arbre *heap)
{
	if (heap->taille == 0)
		return NULL;

	int minIndex = 0;

	for (int i = 1; i < heap->taille; i++)
	{
		if (heap->tableau[i]->frequence < heap->tableau[minIndex]->frequence)
			minIndex = i;
		else if (heap->tableau[i]->frequence == heap->tableau[minIndex]->frequence &&
		         heap->tableau[i]->caractere < heap->tableau[minIndex]->caractere)
			minIndex = i;
	}

	Noeud *minNode = heap->tableau[minIndex];

	heap->tableau[minIndex] = heap->tableau[--heap->taille];
	heapifyDown(heap, minIndex);

	return minNode;
}

void insererArbre(Arbre *heap, Noeud *nouveauNoeud)
{
	if (heap->taille == heap->capacite)
	{
		printf("Arbre plein !\n");
		return;
	}

	int i = heap->taille++;
	heap->tableau[i] = nouveauNoeud;

	heapifyUp(heap, i);
}

void heapifyDown(Arbre *heap, int i)
{
	int plusPetit = i;
	int gauche = 2 * i + 1;
	int droite = 2 * i + 2;

	if (gauche < heap->taille && heap->tableau[gauche]->frequence < heap->tableau[plusPetit]->frequence)
		plusPetit = gauche;

	if (droite < heap->taille && heap->tableau[droite]->frequence < heap->tableau[plusPetit]->frequence)
		plusPetit = droite;

	if (plusPetit != i)
	{
		// Échange et récursion
		Noeud *temp = heap->tableau[i];
		heap->tableau[i] = heap->tableau[plusPetit];
		heap->tableau[plusPetit] = temp;

		heapifyDown(heap, plusPetit);
	}
}

void heapifyUp(Arbre *heap, int i)
{
	int parent = (i - 1) / 2;
	if (i > 0 && heap->tableau[i]->frequence < heap->tableau[parent]->frequence)
	{
		Noeud *temp = heap->tableau[i];
		heap->tableau[i] = heap->tableau[parent];
		heap->tableau[parent] = temp;

		heapifyUp(heap, parent);
	}
}

Noeud *construireArbreHuffman(int frequence[])
{
	Arbre *heap = creerArbre(256);

	for (int i = 0; i < 256; i++)
	{
		if (frequence[i] > 0)
		{
			heap->tableau[heap->taille++] = creerNoeud(i, frequence[i], NULL, NULL);
		}
	}

	while (heap->taille > 1)
	{
		Noeud *noeud1 = extraireMin(heap);
		Noeud *noeud2 = extraireMin(heap);

		if (noeud1->frequence < noeud2->frequence)
		{
			Noeud *temp = noeud1;
			noeud1 = noeud2;
			noeud2 = temp;
		}

		Noeud *nouveauNoeud = creerNoeud('\0', noeud1->frequence + noeud2->frequence, noeud1, noeud2);
		insererArbre(heap, nouveauNoeud);
	}

	return extraireMin(heap);
}

char *codesHuffman[Max_Val_ASCII];

void genererCodes(Noeud *racine, char *code, int profondeur)
{
	if (!racine)
		return;

	if (!racine->gauche && !racine->droite)
	{
		code[profondeur] = '\0';
		codesHuffman[(unsigned char)racine->caractere] = strdup(code);
		printf("Caractère '%c' -> Code Huffman : %s\n", racine->caractere, code);
		return;
	}

	code[profondeur] = '0';
	genererCodes(racine->gauche, code, profondeur + 1);

	code[profondeur] = '1';
	genererCodes(racine->droite, code, profondeur + 1);
}

void ecrireArbreHuffman(FILE *fichier, Noeud *racine)
{
	if (!racine)
		return;

	if (!racine->gauche && !racine->droite)
	{
		fputc('1', fichier);
		fputc(racine->caractere, fichier);
		printf("Écriture : Feuille -> 1 %c (%d)\n", racine->caractere, racine->caractere);
		return;
	}

	fputc('0', fichier);
	printf("Écriture : Noeud interne -> 0\n");

	ecrireArbreHuffman(fichier, racine->gauche);
	ecrireArbreHuffman(fichier, racine->droite);
}

#define BUFFER_SIZE 1024

void ecrireEncodageFichier(FILE *fichier, const char *nomFichier, char *codesHuffman[])
{
	FILE *input = fopen(nomFichier, "r");
	if (!input)
	{
		perror("Erreur ouverture fichier à encoder");
		exit(EXIT_FAILURE);
	}

	unsigned char buffer[BUFFER_SIZE];
	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, input)) > 0)
	{
		for (size_t i = 0; i < bytesRead; i++)
		{
			char *code = codesHuffman[(unsigned char)buffer[i]];
			if (!code)
			{
				printf("Erreur : Aucun code Huffman trouvé pour '%c' (%d)\n", buffer[i], buffer[i]);
				exit(EXIT_FAILURE);
			}
			fputs(code, fichier);
		}
	}

	fclose(input);
}

void ecrireCaracteres(FILE *fichier, Noeud *racine)
{
	if (!racine)
		return;

	if (!racine->gauche && !racine->droite)
	{
		fputc(racine->caractere, fichier);
		printf("Écriture caractère : %c (%d)\n", racine->caractere, racine->caractere);
		return;
	}

	ecrireCaracteres(fichier, racine->gauche);
	ecrireCaracteres(fichier, racine->droite);
}

int calculerNombreBitsUtile(long long tailleOriginale)
{
	int bitsUtile = (tailleOriginale * 8) % 8;
	if (bitsUtile == 0)
		return 8;
	return bitsUtile;
}

long long calculeTailleFichier(const char *nomFichier)
{
	struct stat st;
	if (stat(nomFichier, &st) != 0)
	{
		perror("Erreur lors du calcul de la taille du fichier");
		exit(EXIT_FAILURE);
	}
	return (long long)st.st_size;
}

void compresserFichier(const char *nomFichier, const char *nomOriginal, Noeud *racine)
{
	FILE *fichierCompresse = fopen(nomFichier, "wb");
	if (fichierCompresse == NULL)
	{
		perror("Erreur ouverture fichier compressé");
		exit(EXIT_FAILURE);
	}

	printf("Fichier compressé créé : %s\n", nomFichier);

	// Écriture de l'arbre de Huffman
	printf("Écriture de l'arbre de Huffman...\n");
	ecrireArbreHuffman(fichierCompresse, racine);

	// Marqueur de fin correct (assurez-vous que `lireArbreHuffman()` attend bien '1')
	fputc('1', fichierCompresse);
	printf("Marqueur de fin de l'arbre écrit.\n");

	// Écriture des caractères dans l’ordre du parcours
	printf("Écriture des caractères dans l'ordre de l'arbre...\n");
	ecrireCaracteres(fichierCompresse, racine);

	// Encodage du fichier original
	printf("Encodage du fichier original...\n");
	ecrireEncodageFichier(fichierCompresse, nomOriginal, codesHuffman);

	// Calcul de la taille du fichier original
	long long tailleFichier = calculeTailleFichier(nomOriginal);
	printf("Taille du fichier original à écrire : %lld octets\n", tailleFichier);

	// Calcul du nombre de bits utiles
	int nombreBitsUtile = calculerNombreBitsUtile(tailleFichier);
	fputc(nombreBitsUtile, fichierCompresse);
	printf("Bits utiles écrits : %d\n", nombreBitsUtile);

	// Écriture de la taille du fichier original en 64 bits
	fwrite(&tailleFichier, sizeof(long long), 1, fichierCompresse);

	// Vérification de la structure du fichier compressé
	fseek(fichierCompresse, 0, SEEK_SET);
	printf("\n--- Structure du fichier compressé ---\n");
	int byte;
	while ((byte = fgetc(fichierCompresse)) != EOF)
	{
		printf("%02X ", byte);
	}
	printf("\n-------------------------------------\n");

	// Vérifier la taille réelle du fichier compressé
	fseek(fichierCompresse, 0, SEEK_END);
	long tailleFichierCompresse = ftell(fichierCompresse);
	printf("Taille réelle du fichier compressé : %ld octets\n", tailleFichierCompresse);

	fclose(fichierCompresse);
	printf("Compression terminée !\n");
}

Noeud *lireArbreHuffman(FILE *fichier)
{
	int bit = fgetc(fichier);
	if (bit == EOF)
	{
		perror("Erreur : lecture de l’arbre interrompue !");
		exit(EXIT_FAILURE);
	}

	if (bit == '1')
	{
		char caractere = fgetc(fichier);
		if (caractere == EOF)
		{
			perror("Erreur : caractère non lu !");
			exit(EXIT_FAILURE);
		}
		printf("Noeud feuille lu : %c\n", caractere);
		return creerNoeud(caractere, 0, NULL, NULL);
	}
	else if (bit == '0')
	{
		printf("Noeud interne détecté\n");
		Noeud *gauche = lireArbreHuffman(fichier);
		Noeud *droite = lireArbreHuffman(fichier);
		return creerNoeud('\0', 0, gauche, droite);
	}

	return NULL;
}

void assignerCaracteres(Noeud *racine, FILE *fichier)
{
	if (!racine)
		return;

	if (!racine->gauche && !racine->droite)
	{
		int caractere = fgetc(fichier);
		if (caractere == EOF)
		{
			perror("Erreur : assignation d’un caractère impossible !");
			exit(EXIT_FAILURE);
		}
		racine->caractere = caractere;
		printf("Caractère attribué : %c (%d)\n", racine->caractere, racine->caractere);
		return;
	}

	assignerCaracteres(racine->gauche, fichier);
	assignerCaracteres(racine->droite, fichier);
}

void decoderFichier(FILE *fichierCompresse, FILE *fichierSortie, Noeud *racine, int nombreBitsUtile, long long tailleFichier)
{
	Noeud *noeudActuel = racine;
	int bit, bitCount = 0;
	long long charCount = 0;

	printf("Début de la lecture du fichier compressé...\n");

	while (charCount < tailleFichier)
	{
		int byte = fgetc(fichierCompresse);
		if (byte == EOF)
			break;

		printf("Byte lu : %02X\n", byte);

		for (int i = 7; i >= 0; i--)
		{
			bit = (byte >> i) & 1;
			printf("Bit lu : %d\n", bit); // ✅ Vérification

			bitCount++;

			if (bit == 0)
				noeudActuel = noeudActuel->gauche;
			else
				noeudActuel = noeudActuel->droite;

			if (!noeudActuel->gauche && !noeudActuel->droite)
			{
				fputc(noeudActuel->caractere, fichierSortie);
				printf("Décodé : %c\n", noeudActuel->caractere);
				noeudActuel = racine;
				charCount++;

				if (charCount == tailleFichier)
				{
					printf("Fin de la lecture après %lld caractères.\n", charCount);
					return;
				}
			}

			if (charCount == tailleFichier - 1 && bitCount == nombreBitsUtile)
			{
				printf("Fin de la lecture (bits utiles atteints).\n");
				return;
			}
		}
	}
}

void decompressionFichier(const char *nomFichierCompresse, const char *nomFichierSortie)
{
	FILE *fichierCompresse = fopen(nomFichierCompresse, "rb");
	if (!fichierCompresse)
	{
		perror("Erreur ouverture fichier compressé");
		exit(EXIT_FAILURE);
	}
	printf("Lecture de '%s'...\n", nomFichierCompresse);

	// Reconstruction de l'arbre
	Noeud *racine = lireArbreHuffman(fichierCompresse);
	printf("Arbre reconstruit !\n");

	// Assigner les caractères aux feuilles
	assignerCaracteres(racine, fichierCompresse);
	printf("Caractères associés aux feuilles.\n");

	// Vérifier la position actuelle avant lecture
	printf("Position actuelle avant lecture nombreBitsUtile : %ld\n", ftell(fichierCompresse));

	// Lire le nombre de bits utiles
	int nombreBitsUtile = fgetc(fichierCompresse);
	if (nombreBitsUtile == EOF || nombreBitsUtile < 1 || nombreBitsUtile > 8)
	{
		fprintf(stderr, "Erreur : nombreBitsUtile incorrect ou fichier corrompu !\n");
		exit(EXIT_FAILURE);
	}

	printf("Nombre de bits utiles lu : %d\n", nombreBitsUtile);

	// Vérifier la position avant de lire `tailleFichier`
	printf("Position actuelle avant lecture tailleFichier : %ld\n", ftell(fichierCompresse));

	long long tailleFichier = 0;
	for (int i = 0; i < 8; i++)
	{
		int byte = fgetc(fichierCompresse);
		if (byte == EOF)
		{
			perror("Erreur : tailleFichier non lue !");
			exit(EXIT_FAILURE);
		}
		printf("Byte lu pour taille : %02X\n", byte);
		tailleFichier = (tailleFichier << 8) | byte;
	}
	printf("Taille du fichier original : %lld caractères\n", tailleFichier);

	FILE *fichierSortie = fopen(nomFichierSortie, "w");
	if (!fichierSortie)
	{
		perror("Erreur ouverture fichier de sortie");
		exit(EXIT_FAILURE);
	}

	// Décoder et écrire le texte original
	decoderFichier(fichierCompresse, fichierSortie, racine, nombreBitsUtile, tailleFichier);

	fclose(fichierCompresse);
	fclose(fichierSortie);
	printf("Décompression terminée avec succès dans '%s' !\n", nomFichierSortie);
}

int main()
{
	char *reponse = NULL;
	printf("1 - Compresser un fichier\n2 - Décompresser un fichier\nFaites votre choix : ");
	scanf("%m[^\n]", &reponse);
	while (getchar() != '\n')
		;
	if (strcmp(reponse, "1") == 0)
	{
		printf("Nous allons compresser votre fichier\nDonnez nous le nom du fichier à compresser : ");
		char *InputFic = NULL;
		scanf("%m[^\n]", &InputFic);

		int frequence[Max_Val_ASCII];

		FillTabHzChar(InputFic, frequence);

		printf("\nFréquence des caractères :\n");
		ShowHz(frequence);

		Noeud *racine = construireArbreHuffman(frequence);

		char code[Max_Val_ASCII]; // Stock temporaire du code
		printf("\nCodes Huffman générés :\n");
		genererCodes(racine, code, 0);
		while (getchar() != '\n')
			;

		printf("Donnez nous le nom du fichier où sera écrit la compression (.huff) : ");
		char *NomFicTemp = NULL;
		scanf("%m[^\n]", &NomFicTemp);
		while (getchar() != '\n')
			;
		char *NomFic = NULL;
		if (strstr(NomFicTemp, ".huff") == NULL)
		{
			NomFic = malloc(strlen(NomFicTemp) + 1);
			if (NomFic == NULL)
			{
				perror("Erreur d'allocation de mémoire");
				exit(EXIT_FAILURE);
			}
			sprintf(NomFic, "%s.huff", NomFicTemp);
			printf("%s\n", NomFicTemp);
		}
		else
		{
			NomFic = malloc(strlen(NomFicTemp));
			if (NomFic == NULL)
			{
				perror("Erreur d'allocation de mémoire");
				exit(EXIT_FAILURE);
			}
			sprintf(NomFic, "%s", NomFicTemp);
			printf("%s\n", NomFicTemp);
		}
		/*Faire la compression*/
		compresserFichier(NomFic, InputFic, racine);
		printf("Compression finie !");
		free(NomFicTemp);
		NomFicTemp = NULL;
		free(NomFic);
		NomFic = NULL;
		free(reponse);
		reponse = NULL;
	}
	else if (strcmp(reponse, "2") == 0)
	{
		printf("Nous allons décompresser votre fichier dans le dossier courant.\n");

		printf("Nom du fichier compressé à décompresser : ");
		char *NomFicCompresse = NULL;
		scanf("%m[^\n]", &NomFicCompresse);
		while (getchar() != '\n')
			;

		printf("Nom du fichier de sortie (reconstruit) : ");
		char *NomFicSortie = NULL;
		scanf("%m[^\n]", &NomFicSortie);
		while (getchar() != '\n')
			;

		decompressionFichier(NomFicCompresse, NomFicSortie);

		free(NomFicCompresse);
		free(NomFicSortie);
	}

	else
	{
		printf("Erreur de format saisi.\nChoisissez entre 1 et 2 la prochaine fois !!! Je ne vous fais plus confiance pour continuer :'(");
		free(reponse);
		reponse = NULL;
		exit(EXIT_FAILURE);
	}
}