#ifndef HASHING_H
#define HASHING_H

#define MAX_SIZE 6         // Longueur maximale du mot de passe
#define MAX_TRIES 10000000 // Nombre max d'essais
#define CHARSET_FILE "charset.txt"
#define TARGET_FILE "target.txt"
#define WORDLIST_FILE "wordlist.txt"

void computeMD5(const char *input, char *output);
void computeSHA1(const char *input, char *output);

#endif
