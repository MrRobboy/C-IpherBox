#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "port_scan.h"
#include "network_scanner.h"
#include "menu.h"
#include "random_quotes_from_trancho.h"
void run_menu()
{
    int choix;

    printf("   ______       ____        __                 ____              \n");
    printf("  / ____/      /  _/____   / /_   ___   _____ / __ ) ____   _  __\n");
    printf(" / /   ______  / / / __ \\ / __ \\ / _ \\ / ___// __  |/ __ \\ | |/_/\n");
    printf("/ /___/_____/_/ / / /_/ // / / //  __// /   / /_/ // /_/ /_>  <  \n");
    printf("\\____/      /___// .___//_/ /_/ \\___//_/   /_____/ \\____//_/|_|  \n");
    printf("                /_/                                              \n\n");

    random_quotes_from_trancho();
    while (1)
    {
        

        printf("1. Scanner une IP unique\n");
        printf("2. Scanner un réseau entier\n");
        printf("3. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        if (choix == 1)
        {
            char ip[INET_ADDRSTRLEN];
            int start_port, end_port;

            printf("Entrez l'adresse IP : ");
            scanf("%s", ip);
            printf("Entrez le port de départ : ");
            scanf("%d", &start_port);
            printf("Entrez le port de fin : ");
            scanf("%d", &end_port);


    scan_ip(ip, start_port, end_port);
}

        else if (choix == 2)
        {
            char cidr[32];
            int start_port, end_port;

            printf("Entrez un réseau (ex. 192.168.1.0/24) : ");
            scanf("%s", cidr);
            printf("Entrez le port de départ : ");
            scanf("%d", &start_port);
            printf("Entrez le port de fin : ");
            scanf("%d", &end_port);

            scan_réseau(cidr, start_port, end_port);
        }
        else if (choix == 3)
        {
            printf("Au revoir !\n");
            break;
        }
        else
        {
            printf("Option invalide. Veuillez réessayer.\n");
        }
    }
}