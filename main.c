#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdint.h>

#define TIMEOUT_SEC 1
#define MAX_THREADS 100

const char* get_service_name(int port) {
    struct servent *service;
    service = getservbyport(htons(port), "tcp");
    return (service != NULL) ? service->s_name : "Unknown";
}

int scan_port(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in target;
    fd_set fdset;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return 0;
    }

    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &target.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return 0;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1 || fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        close(sockfd);
        return 0;
    }

    int res = connect(sockfd, (struct sockaddr *)&target, sizeof(target));
    if (res < 0 && errno == EINPROGRESS) {
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
        struct timeval timeout = {TIMEOUT_SEC, 0};

        if (select(sockfd + 1, NULL, &fdset, NULL, &timeout) > 0) {
            int so_error;
            socklen_t len = sizeof(so_error);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error == 0) {
                close(sockfd);
                return 1;
            }
        }
    }

    close(sockfd);
    return 0;
}

void nbrips(const char *cidr, char ***ip_list, int *ip_count) {
    char base_ip[INET_ADDRSTRLEN];
    int mask_bits;
    sscanf(cidr, "%15[^/]/%d", base_ip, &mask_bits);

    struct in_addr addr;
    inet_pton(AF_INET, base_ip, &addr);

    uint32_t base = ntohl(addr.s_addr);
    uint32_t num_ips = 1 << (32 - mask_bits);

    *ip_list = malloc(num_ips * sizeof(char *));
    *ip_count = num_ips;

    for (uint32_t i = 0; i < num_ips; i++) {
        (*ip_list)[i] = malloc(INET_ADDRSTRLEN);
        struct in_addr current_addr;
        current_addr.s_addr = htonl(base + i);
        inet_ntop(AF_INET, &current_addr, (*ip_list)[i], INET_ADDRSTRLEN);
    }
}

void scan_ip(const char *ip, int start_port, int end_port) {
    printf("Scan IP %s du port %d à %d...\n", ip, start_port, end_port);

    for (int port = start_port; port <= end_port; port++) {
        if (scan_port(ip, port)) {
            const char* service_name = get_service_name(port);
            printf("Port %d ouvert (%s)\n", port, service_name);
        }
    }

    printf("Scan de l'IP %s terminé.\n", ip);
}

void scan_réseau(const char *cidr, int start_port, int end_port) {
    char **ip_list;
    int ip_count;

    nbrips(cidr, &ip_list, &ip_count);
    printf("Scan réseau %s (%d hosts) du port %d à %d avec %d threads...\n", cidr, ip_count, start_port, end_port, MAX_THREADS);

    typedef struct {
        char **ip_list;
        int ip_count;
        int current_index;
        int start_port;
        int end_port;
        pthread_mutex_t *lock;
    } thread_pool_t;

    pthread_t threads[MAX_THREADS];
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    thread_pool_t pool = {
        .ip_list = ip_list,
        .ip_count = ip_count,
        .current_index = 0,
        .start_port = start_port,
        .end_port = end_port,
        .lock = &lock
    };

    void* thread_pool_worker(void* args) {
        thread_pool_t *pool = (thread_pool_t*)args;
        while (1) {
            pthread_mutex_lock(pool->lock);
            if (pool->current_index >= pool->ip_count) {
                pthread_mutex_unlock(pool->lock);
                break;
            }

            int ip_index = pool->current_index++;
            pthread_mutex_unlock(pool->lock);

            for (int port = pool->start_port; port <= pool->end_port; port++) {
                if (scan_port(pool->ip_list[ip_index], port)) {
                    const char* service_name = get_service_name(port);
                    printf("IP: %s, Port: %d ouvert (%s)\n", pool->ip_list[ip_index], port, service_name);
                }
            }
        }

        return NULL;
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_pool_worker, &pool) != 0) {
            perror("pthread_create");
        }
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < ip_count; i++) {
        free(ip_list[i]);
    }
    free(ip_list);
    pthread_mutex_destroy(&lock);

    printf("Scan du réseau %s terminé.\n", cidr);
}

int main() {
    int choix;

    printf("   ______       ____        __                 ____              \n");
    printf("  / ____/      /  _/____   / /_   ___   _____ / __ ) ____   _  __\n");
    printf(" / /   ______  / / / __ \\ / __ \\ / _ \\ / ___// __  |/ __ \\ | |/_/\n");
    printf("/ /___/_____/_/ / / /_/ // / / //  __// /   / /_/ // /_/ /_>  <  \n");
    printf("\\____/      /___// .___//_/ /_/ \\___//_/   /_____/ \\____//_/|_|  \n");
    printf("                /_/                                              \n\n");

    while (1) {
        printf("\n=============================\n");
        printf("  Bienvenue Mr. Trancho \n");
        printf("=============================\n");
        printf("1. Scanner une IP unique\n");
        printf("2. Scanner un réseau entier (CIDR)\n");
        printf("3. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        if (choix == 1) {
            char ip[INET_ADDRSTRLEN];
            int start_port, end_port;

            printf("Entrez l'adresse IP : ");
            scanf("%s", ip);
            printf("Entrez le port de départ : ");
            scanf("%d", &start_port);
            printf("Entrez le port de fin : ");
            scanf("%d", &end_port);

            scan_ip(ip, start_port, end_port);

        } else if (choix == 2) {
            char cidr[32];
            int start_port, end_port;

            printf("Entrez le réseau CIDR (ex. 192.168.1.0/24) : ");
            scanf("%s", cidr);
            printf("Entrez le port de départ : ");
            scanf("%d", &start_port);
            printf("Entrez le port de fin : ");
            scanf("%d", &end_port);

            scan_réseau(cidr, start_port, end_port);

        } else if (choix == 3) {
            printf("Au revoir !\n");
            break;
        } else {
            printf("Option invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
