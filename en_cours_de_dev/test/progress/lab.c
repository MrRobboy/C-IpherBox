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

		// Création du nœud interne fusionné
		Noeud *nouveauNoeud = creerNoeud('\0', gauche->frequence + droite->frequence, gauche, droite);

		// Insertion du nœud fusionné
		insererArbre(heap, nouveauNoeud);
	}

	return extraireMin(heap); // La racine de l’arbre
}

int main()
{
	int frequence[Max_Val_ASCII];
	FillTabHzChar("test.txt", frequence);
	ShowHz(frequence);
	return 0;
}