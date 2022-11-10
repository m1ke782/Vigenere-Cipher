#ifndef VIN_HEADER
#define VIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vin_encode_str(char* txt, int txtlen, char* key, int keylen);
char* vin_encode(char* txt, int txtlen, char* key, int keylen);
char* vin_bruteforce_key(char* txt, int txtlen, int keylen, float* bestFitness);

#endif