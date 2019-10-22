/*
** hash.c for hash func
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Wed Feb  6 19:07:13 2019 
** Last update Wed Feb  6 19:07:16 2019 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/sha.h>
#include "server.h"

/*
** Gives sha256sum of str
*/
char			*sha256(const char *str)
{
  unsigned char		hash[SHA256_DIGEST_LENGTH] = {0};
  SHA256_CTX		sha256;
  char			*output_buffer;

  if (!(output_buffer = calloc(1, sizeof(char) * ((SHA256_DIGEST_LENGTH * 2) + 1))))
    return (NULL);
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str, NONCE_LENGTH + strlen(PASSWORD));
  SHA256_Final(hash, &sha256);
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    sprintf(output_buffer + (i * 2), "%02x", hash[i]);
  output_buffer[64] = 0;
  return (output_buffer);
}
