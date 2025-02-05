#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		return;
	}

	fputc('0', fichier);
	ecrireArbreHuffman(fichier, racine->gauche);
	ecrireArbreHuffman(fichier, racine->droite);
}

void compresserFichier(const char *nomFichier, Noeud *racine, int *frequence)
{
	FILE *fichierCompresse = fopen(nomFichier, "wb");
	if (!fichierCompresse)
	{
		perror("Erreur ouverture fichier compressé");
		exit(EXIT_FAILURE);
	}

	ecrireArbreHuffman(fichierCompresse, racine);

	fclose(fichierCompresse);
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
		printf("Nous allons compresser votre fichier\nDonnez nous le nom du fichier à compresser: ");
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

		printf("Donnez nous le nom du fichier où sera écrit la compression (.huff) :");
		char *NomFicTemp = NULL;
		scanf("%m[^\n]", &NomFicTemp);
		while (getchar() != '\n')
			;
		char *NomFic = NULL;
		if (strstr(NomFicTemp, ".huff") == NULL)
		{
			NomFic = malloc(strlen(NomFicTemp));
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
		compresserFichier(InputFic, racine, frequence);
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
		/*Faire la décompression*/
		printf("Décompression faite !");
		free(reponse);
		reponse = NULL;
	}
	else
	{
		printf("Erreur de format saisi.\nChoisissez entre 1 et 2 la prochaine fois !!! Je ne vous fais plus confiance pour continuer :'(");
		free(reponse);
		reponse = NULL;
		exit(EXIT_FAILURE);
	}
}