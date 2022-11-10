//Responisble for managing the trigram source file and to check for string fitness

#ifndef TRIS_HEADER
#define TRIS_HEADER

#include <stdio.h>
#include <stdlib.h>

extern int* TRIGRAMS;
void trigrams_load(const char* file);
void trigrams_free();
float trigrams_fitness(char* txt, int len);

#endif