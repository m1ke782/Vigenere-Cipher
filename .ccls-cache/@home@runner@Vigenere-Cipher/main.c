#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "tris.h"
#include "vin.h"


long long time() 
{
  struct timeval te; 
  gettimeofday(&te, NULL);
  long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
  return milliseconds;
}

char* loadfile(char* file, long* size)
{
  FILE* fp = fopen (file, "rb");
  fseek(fp, 0L, SEEK_END);
  long lSize = ftell(fp);
  rewind(fp);
  char* buffer = calloc(1, lSize+1);
  fread(buffer, lSize, 1, fp);
  fclose(fp);
  *size = lSize;
  return buffer;
}

int main(void) 
{
  int keylen=5;
  long long startTime = time();

  //load files
  trigrams_load("trigrams.txt");
  long cipherlen=0;
  char* cipher = loadfile("cipher.txt",&cipherlen);
  //info
  printf("Fetched files in %lldms.\nStarting decode\n-----~-----\n",time()-startTime);


  char* txt = vin_encode(cipher,cipherlen,"JODIE",5);
  printf("%s\n",txt);
  free(txt);


  //decipher
  float fit = 0;
  char* key = vin_bruteforce_key(cipher,cipherlen,keylen,&fit);
  printf("Done in %lldms\n",time()-startTime);
  printf("Found key : <%s> with fitness <%f>\n",key,fit);
  printf("Decoded text : \n");
  char* decoded = vin_encode(cipher,cipherlen,key,keylen);
  printf("%s\n",decoded);

  //housekeeping
  free(cipher);
  free(decoded);
  free(key);
  return 0;
}