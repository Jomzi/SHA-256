#include <stdio.h>
#include <stdint.h>

union  msgblock {
  uint8_t   e[64];
  uint32_t  t[16];
  uint64_t  s[8];
};


int main(int argc, char *argv[]){

  union msgblock M;

  uint64_t nobytes;  

  FILE* f;

  f = fopen(argv[1], "r");
  
  while (!feof(f)){
    nobytes = fread(M.e, 1, 64, f);
    printf("%llu\n", nobytes);
  }
 
  fclose(f);

  return 0;  
}	
