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
	{
		return NULL;
	}

	Noeud *minNode = heap->tableau[0];
	heap->tableau[0] = heap->tableau[--heap->taille];
	heapifyDown(heap, 0);

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
		Noeud *gauche = extraireMin(heap);
		Noeud *droite = extraireMin(heap);

		Noeud *nouveauNoeud = creerNoeud('\0', gauche->frequence + droite->frequence, gauche, droite);

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

int main()
{
	int frequence[Max_Val_ASCII];

	FillTabHzChar("test.txt", frequence);

	printf("\nFréquence des caractères :\n");
	ShowHz(frequence);

	Noeud *racine = construireArbreHuffman(frequence);

	char code[Max_Val_ASCII]; // Stock temporaire du code
	printf("\nCodes Huffman générés :\n");
	genererCodes(racine, code, 0);

	return 0;
}