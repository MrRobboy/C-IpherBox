#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "cidr_to_ips.h"

void nbrips(const char *cidr, char ***ip_list, int *ip_count)
{
    char base_ip[INET_ADDRSTRLEN];
    int mask_bits;
    sscanf(cidr, "%15[^/]/%d", base_ip, &mask_bits);

    struct in_addr addr;
    inet_pton(AF_INET, base_ip, &addr);

    uint32_t base = ntohl(addr.s_addr);
    uint32_t num_ips = 1 << (32 - mask_bits);

    *ip_list = malloc(num_ips * sizeof(char *));
    *ip_count = num_ips;

    for (uint32_t i = 0; i < num_ips; i++)
    {
        (*ip_list)[i] = malloc(INET_ADDRSTRLEN);
        struct in_addr current_addr;
        current_addr.s_addr = htonl(base + i);
        inet_ntop(AF_INET, &current_addr, (*ip_list)[i], INET_ADDRSTRLEN);
    }
}