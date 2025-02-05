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
#include "port_scan.h"
#define TIMEOUT_SEC 5 


const char *get_service_name(int port)
{
    struct servent *service;
    service = getservbyport(htons(port), "tcp");
    return (service != NULL) ? service->s_name : "Unknown";
}

int scan_port(const char *ip, int port)
{
    int sockfd;
    struct sockaddr_in target;
    fd_set fdset;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket");
        return 0;
    }

    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &target.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(sockfd);
        return 0;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1 || fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl");
        close(sockfd);
        return 0;
    }

    int res = connect(sockfd, (struct sockaddr *)&target, sizeof(target));
    if (res < 0 && errno == EINPROGRESS)
    {
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
        struct timeval timeout = {TIMEOUT_SEC, 0};

        if (select(sockfd + 1, NULL, &fdset, NULL, &timeout) > 0)
        {
            int so_error;
            socklen_t len = sizeof(so_error);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error == 0)
            {
                close(sockfd);
                return 1;
            }
        }
    }

    close(sockfd);
    return 0;
}

void scan_ip(const char *ip, int start_port, int end_port)
{
    printf("Scan IP %s du port %d à %d...\n", ip, start_port, end_port);

    for (int port = start_port; port <= end_port; port++)
    {
        if (scan_port(ip, port))
        {
            const char *service_name = get_service_name(port);
            printf("Port %d ouvert (%s)\n", port, service_name);
        }
    }

    printf("Scan de l'IP %s terminé.\n", ip);
}