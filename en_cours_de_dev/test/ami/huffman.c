#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// Structure d'un nœud
struct MinHeapNode
{
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

// Tas min pour gérer la construction de l'arbre Huffman
struct MinHeap
{
	unsigned size;
	unsigned capacity;
	struct MinHeapNode **array;
};

// Création d'un nœud
struct MinHeapNode *newNode(char data, unsigned freq)
{
	struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
	temp->data = data;
	temp->freq = freq;
	temp->left = temp->right = NULL;
	return temp;
}

// Création du tas
struct MinHeap *createMinHeap(unsigned capacity)
{
	struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
	return minHeap;
}

// Échange deux nœuds
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
	struct MinHeapNode *t = *a;
	*a = *b;
	*b = t;
}

// Organise le tas min
void minHeapify(struct MinHeap *minHeap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx)
	{
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// Extraction du nœud min
struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
	struct MinHeapNode *temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

// Insère un nœud dans le tas
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

// Construit l'arbre Huffman
struct MinHeapNode *buildHuffmanTree(char data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;
	struct MinHeap *minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
		minHeapify(minHeap, i);

	while (minHeap->size != 1)
	{
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}

	return extractMin(minHeap);
}

// Génération des codes
void printCodes(struct MinHeapNode *root, int arr[], int top)
{
	if (root->left)
	{
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right)
	{
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	if (!(root->left) && !(root->right))
	{
		printf("%c: ", root->data);
		for (int i = 0; i < top; ++i)
			printf("%d", arr[i]);
		printf("\n");
	}
}

// Point d'entrée de Huffman
void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode *root = buildHuffmanTree(data, freq, size);
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
}
