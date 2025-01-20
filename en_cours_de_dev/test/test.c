#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char commande[256];
	strcpy(commande, "dir /w /aa");
	system(commande);
}