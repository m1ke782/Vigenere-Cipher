#include "vin.h"
#include "tris.h"

void vin_encode_str(char* txt, int txtlen, char* key, int keylen)
{
  for (int i = 0; i < txtlen; i++)
  {
    int vina = i % keylen;
    int code = (*(key+vina)-'A') + (*(txt+i)-'A');
    code = code%26;
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
    *(key+i) = 'A';

  //best key
  char* bestKey = (char*)calloc(keylen+1, sizeof(char));
  strcpy(bestKey,"????");
  double bestFitness = 0;

  int looping = 1;
  while (looping)
  {

    char* encoded = vin_encode(txt,txtlen,key,keylen);
    float fit = trigrams_fitness(encoded,txtlen);

    if (fit > bestFitness)
    {
      bestFitness = fit;
      strcpy(bestKey,key);
    }
  
    
    //step up
    *(key) += 1;
    for (int i = 0; i < keylen; i++)
    {
      if (*(key+i) > 'Z')
      {
        //break condition
        if (i + 1 == keylen)
        {
          looping=0;
          break;
        }
        //step up
        *(key+i) = 'A';
        *(key+i+1) += 1;
      }
    }
  }

  free(key);
  *bestFitness = 
  return bestKey;
}