#ifndef HASHING_H
#define HASHING_H

#include <stdint.h>

#define MD5_BLOCK_SIZE 16
#define SHA1_BLOCK_SIZE 20

// Déclarations des fonctions MD5
void computeMD5(const char *input, char *output);

// Déclarations des fonctions SHA-1
void computeSHA1(const char *input, char *output);

#endif
