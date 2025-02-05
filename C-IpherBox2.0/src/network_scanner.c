#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "cidr_to_ips.h"
#include "port_scan.h"
#include "network_scanner.h"

#define MAX_THREADS 100

typedef struct
{
    char **ip_list;
    int ip_count;
    int current_index;
    int start_port;
    int end_port;
    pthread_mutex_t *lock;
} thread_pool_t;

static void *thread_pool_worker(void *args)
{
    thread_pool_t *pool = (thread_pool_t *)args;
    while (1)
    {
        pthread_mutex_lock(pool->lock);
        if (pool->current_index >= pool->ip_count)
        {
            pthread_mutex_unlock(pool->lock);
            break;
        }

        int ip_index = pool->current_index++;
        pthread_mutex_unlock(pool->lock);

        for (int port = pool->start_port; port <= pool->end_port; port++)
        {
            if (scan_port(pool->ip_list[ip_index], port))
            {
                const char *service_name = get_service_name(port);
                printf("IP: %s, Port: %d ouvert (%s)\n", pool->ip_list[ip_index], port, service_name);
            }
        }
    }

    return NULL;
}

void scan_réseau(const char *cidr, int start_port, int end_port)
{
    char **ip_list;
    int ip_count;

    nbrips(cidr, &ip_list, &ip_count);
    printf("Scan réseau %s (%d hosts) du port %d à %d avec %d threads...\n", cidr, ip_count, start_port, end_port, MAX_THREADS);

    pthread_t threads[MAX_THREADS];
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    thread_pool_t pool = {
        .ip_list = ip_list,
        .ip_count = ip_count,
        .current_index = 0,
        .start_port = start_port,
        .end_port = end_port,
        .lock = &lock};

    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, thread_pool_worker, &pool) != 0)
        {
            perror("pthread_create");
        }
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < ip_count; i++)
    {
        free(ip_list[i]);
    }
    free(ip_list);
    pthread_mutex_destroy(&lock);

    printf("Scan du réseau %s terminé.\n", cidr);
}