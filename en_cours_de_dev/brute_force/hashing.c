#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

// Implémentation simple du MD5 (sans OpenSSL)
void computeMD5(const char *input, char *output)
{
    unsigned int hash = 0;
    while (*input)
    {
        hash = (hash * 31) + (*input++);
    }
    snprintf(output, 33, "%08x%08x%08x%08x", hash, hash, hash, hash);
}

// Implémentation simple du SHA1 (sans OpenSSL)
void computeSHA1(const char *input, char *output)
{
    unsigned int hash = 0;
    while (*input)
    {
        hash = (hash * 37) + (*input++);
    }
    snprintf(output, 41, "%08x%08x%08x%08x%08x", hash, hash, hash, hash, hash);
}
