#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void random_quotes_from_trancho() {
    const char *messages[] = {
        "Bienvenue Mr. Trancho",
        "Bienvenue en Langage C",
        "Avez vous fini tout les exercices du support de cours ?",
        "Ce projet vaut au moins 20/20",
        "Vous gagnez une souris imprimee en 3D bravo les eleves",
        "Content de vous revoir Mr. Trancho",
        "C isn't hard: void (*(*f[])())()",
        "Le C C trivial, bien entendu",
        
    };

    int nombreMessages = sizeof(messages) / sizeof(messages[0]);

    srand(time(NULL));

    int index = rand() % nombreMessages;

    printf("\n=======================================================================================\n");
    printf("  %s  \n", messages[index]);
    printf("=======================================================================================\n");


}
