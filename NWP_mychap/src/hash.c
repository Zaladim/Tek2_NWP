/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Hashing
*/

#include "mychap.h"

char *hash(unsigned char *salt, unsigned char *msg, size_t n)
{
    unsigned char md[SHA256_DIGEST_LENGTH];
    char tmp[3];
    char *hash = malloc(SHA256_DIGEST_LENGTH * 2);

    if (!hash)
        return NULL;
    SHA256_CTX sha;
    SHA256_Init(&sha);
    SHA256_Update(&sha, salt, SHA_LENGTH);
    SHA256_Update(&sha, msg, strlen(msg));
    SHA256_Final(md, &sha);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(tmp, "%02x", md[i]);
        strncpy(hash + (i * 2), tmp, 2);
    }
    return (hash);
}