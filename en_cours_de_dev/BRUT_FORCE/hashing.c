#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hashing.h"

// Fonction pour convertir un hash en string hexadécimale
void hash_to_string(unsigned char *hash, int hash_len, char *output)
{
    for (int i = 0; i < hash_len; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[hash_len * 2] = '\0';
}

// === Implémentation de MD5 ===
typedef struct
{
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
} MD5_CTX;

// Initialisation des valeurs du MD5
void md5_init(MD5_CTX *ctx)
{
    ctx->count[0] = ctx->count[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}

// MD5 Transform (simplifié)
void md5_transform(MD5_CTX *ctx, const unsigned char data[])
{
    // Ici, tu devras ajouter l'algorithme complet de MD5 si nécessaire
}

// Mise à jour du MD5
void md5_update(MD5_CTX *ctx, const unsigned char *data, size_t len)
{
    memcpy(ctx->buffer, data, len);
}

// Finalisation du MD5
void md5_final(MD5_CTX *ctx, unsigned char hash[])
{
    memcpy(hash, ctx->state, 16);
}

// Fonction MD5 complète
void computeMD5(const char *input, char *output)
{
    MD5_CTX ctx;
    unsigned char digest[MD5_BLOCK_SIZE];

    md5_init(&ctx);
    md5_update(&ctx, (unsigned char *)input, strlen(input));
    md5_final(&ctx, digest);

    hash_to_string(digest, MD5_BLOCK_SIZE, output);
}

// === Implémentation de SHA-1 ===
typedef struct
{
    uint32_t state[5];
    uint32_t count[2];
    unsigned char buffer[64];
} SHA1_CTX;

// Initialisation du SHA-1
void sha1_init(SHA1_CTX *ctx)
{
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
}

// SHA-1 Transform (simplifié)
void sha1_transform(SHA1_CTX *ctx, const unsigned char data[])
{
    // Ici, tu devras ajouter l'algorithme complet de SHA-1 si nécessaire
}

// Mise à jour du SHA-1
void sha1_update(SHA1_CTX *ctx, const unsigned char *data, size_t len)
{
    memcpy(ctx->buffer, data, len);
}

// Finalisation du SHA-1
void sha1_final(SHA1_CTX *ctx, unsigned char hash[])
{
    memcpy(hash, ctx->state, 20);
}

// Fonction SHA-1 complète
void computeSHA1(const char *input, char *output)
{
    SHA1_CTX ctx;
    unsigned char digest[SHA1_BLOCK_SIZE];

    sha1_init(&ctx);
    sha1_update(&ctx, (unsigned char *)input, strlen(input));
    sha1_final(&ctx, digest);

    hash_to_string(digest, SHA1_BLOCK_SIZE, output);
}
