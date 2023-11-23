#include "vin.h"
#include "tris.h"

int randbetween(int max)
{
  static int seed = 0;
  seed++;
  srand(time(0) + seed);
  return rand()%max;
}

int mod26(int n)
{
  return ((n % 26) + 26) % 26;
}

void vin_encode_str(char* txt, int txtlen, char* key, int keylen)
{
  for (int i = 0; i < txtlen; i++)
  {
    int vina = i % keylen;
    int code = (*(txt+i)-'A') - (*(key+vina)-'A');
    code = mod26(code);
    *(txt + i) = code + 'A';
  }
}

char* vin_encode(char* txt, int txtlen, char* key, int keylen)
{
  char* output = (char*)calloc(txtlen+1, sizeof(char));
  strcpy(output,txt);
  vin_encode_str(output, txtlen, key, keylen);
  return output;
}


char* vin_bruteforce_key(char* txt, int txtlen, int keylen, float* bestfit)
{  
  //generate key
  char* key = (char*)calloc(keylen+1, sizeof(char));
  for (int i = 0; i < keylen; i++)
    *(key+i) = randbetween(26)+'A';
  float bestFitness = 0;

  for (int i = 0; i < 10000; i++)
  {
    //get fitness before
    char* encodeBefore = vin_encode(txt,txtlen,key,keylen);
    float fitnessBefore = trigrams_fitness(encodeBefore,txtlen);
    free(encodeBefore);

    
    //generate random mutation
    int toChange = randbetween(keylen);
    int changeTo = randbetween(26);

    //make random mutation
    char charBefore = *(key+toChange);
    *(key+toChange)=changeTo+'A';


    //get fitness after
    char* encodeAfter = vin_encode(txt,txtlen,key,keylen);
    float fitnessAfter = trigrams_fitness(encodeAfter,txtlen);
    free(encodeAfter);


    if (fitnessAfter <= fitnessBefore)
    {
      //bad mutation, revert
      *(key+toChange) = charBefore;
    }
    else
    {
      bestFitness = fitnessAfter;
      printf("%f+\n",fitnessAfter-fitnessBefore);
    }
  }

  printf("-----~-----\n");
  *bestfit = bestFitness;
  return key;
}


/*
char* vin_bruteforce_key(char* txt, int txtlen, int keylen, float* bestfit)
{  
  //generate key
  char* key = (char*)calloc(keylen+1, sizeof(char));
  for (int i = 0; i < keylen; i++)
    *(key+i) = 'A';

  strcpy(key,"PSMO");


  for (int i = 0; i < 10000; i++)
  {
    //get fitness before
    char* encodeBefore = vin_encode(txt,txtlen,key,keylen);
    float fitnessBefore = trigrams_fitness(encodeBefore,txtlen);
    //printf("%f) %s\n",fitnessBefore,encodeBefore);
    free(encodeBefore);

    //make random mutation
    int toChange = randbetween(keylen);
    int changeTo = randbetween(26);
    char keyBefore = *(key+toChange);
    *(key+toChange) = changeTo + 'A';

    //get fitness after
    char* encodeAfter = vin_encode(txt,txtlen,key,keylen);
    float fitnessAfter = trigrams_fitness(encodeAfter,txtlen);
    free(encodeAfter);

    //revert mutation if not beneficial
    if (fitnessAfter < fitnessBefore)
    {
      *(key+toChange) = keyBefore;
    }

    //apply changes
    if (fitnessBefore > *bestfit) *bestfit = fitnessBefore;
    if (fitnessAfter > *bestfit) *bestfit = fitnessAfter;
  }

  
  return key;
}
*/
