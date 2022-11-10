#include "tris.h"

int* TRIGRAMS = NULL;

void trigrams_load(const char* file)
{
  TRIGRAMS = (int*)malloc(sizeof(int) * 17576);
  FILE* f_src = fopen(file, "r");
  for (int i = 0; i < 17576; i++)
    fscanf(f_src, "%d", TRIGRAMS+i);
}
void trigrams_free()
{
  free(TRIGRAMS);
  TRIGRAMS = NULL;
}

float trigrams_fitness(char* txt, int len)
{
  if (TRIGRAMS == NULL)
  {
    perror("Trigrams not initialised\n");
    exit(1);
  }
  int* gramCount = (int*)calloc(17576, sizeof(int));
  float fitness = 0;
  for (int i = 0; i < len - 2; i++)
  {
    int c1 = *(txt + i) - 'A';
    int c2 = *(txt + i + 1) - 'A';
    int c3 = *(txt + i + 2) - 'A';
    int code = c1*676 + c2*26 + c3;
    int count = *(TRIGRAMS+code);

    if (count <= 0) continue;
    fitness += 1.0f / (float)(count);
  }
  fitness = 1.0f/fitness;
  return fitness;
}