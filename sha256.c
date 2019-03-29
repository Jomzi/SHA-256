// James O'Hanlon, 2019
// The Secure Hash Algorithm, 256 bit version 
// https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=919060

// The usual input/output header file.
#include <stdio.h> 
// For using fixed bit lenght integer.
#include <stdint.h>

// Represents a message block.
union msgblock {
  uint8_t  e[64];
  uint32_t t[16];
  uint64_t s[8];
};

// A flag for where we are in reading the file.
enum status {READ, PAD0, PAD1, FINISH};



// See Section 4.1.2 for definitions.
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// See Section 3.2 for defintions.
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

// See Section 4.1.2 for definitions.
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

// See Section 4.1.2 for definitions.
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

void sha256(FILE *f);

// Retrieves the next message block.
int nextmsgblock(FILE *f, union msgblock *M, enum status *S, int *nobits);

// Start of the show.
int main(int argc, char *argv[]){

  FILE* f;
  f = fopen(argv[1], "r");  
  
  sha256(f);

  return 0;
}  


void sha256(){
   
  // The current message block
  union msgblock M;

  // The number of bits read from  the file.
  uint64_t nobits = 0;

  // The status of the message blocks, in terms of padding.
  enum status S = READ;

  // The K constants, defined in Section 4.2.2.
  uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 
  };


  // Message schedule (Section 6.2).
  uint32_t W[64];
  // Working varibles (Section 6.2).
  uint32_t a, b, c, d, e, f, g, h;
  // Two temporary variables (Section 6.2).
  uint32_t T1, T2;

  // The Hash value (Section 6.2).
  // The value come from Section 5.3.3.
  uint32_t H[8] = {
      0x6a09e667
    , 0xbb67ae85
    , 0x3c6ef372
    , 0xa54ff53a
    , 0x510e527f	       
    , 0x9b05688c
    , 0x1f83d9ab
    , 0x5be0cd19
  };
  

  // For looping.
  int i,t;

  while (nextmsgblock(f, M, S, nobits)){
  
  // Loop through message blocks as per page 22.
  for(i = 0; i < 1; i++){
  
  
  // From page 22, W[t] = M[t] for 0 <= t <= 15.
  for(t = 0; t < 16; t++)
    W[t] = M[t];

  // From page 22, W[t] = ...
  for (t = 16; t < 64; t++)
    W[t] =  sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
  
  // Initialis a, b, c, .., h as per Step 2, Page 22.
  a = H[0]; b = H[1]; c = H[2]; d = H[3];
  e = H[4]; f = H[5]; g = H[6]; h = H[7];
  
  // Step 3.
  for (t = 0; t < 64; t++){
    T1 = h + SIG1(e) + Ch(e, f, g) + K[t] +  W[t];
    T2 = SIG0(a) + Maj(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b; 
    b = a;  
    a = T1 + T2;  
  }

  // Step 4.
  H[0] = a + H[0];
  H[1] = b + H[1];
  H[2] = c + H[2];
  H[3] = d + H[3];
  H[4] = e + H[4];
  H[5] = f + H[5];
  H[6] = g + H[6];
  H[7] = h + H[7];

  }
  printf("%x %x %x %x %x %x %x %x\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
} 


// See Section 3.2 for defintions.
uint32_t rotr(uint32_t n, uint32_t x){
  return(x >> n) | (x << (32 - n));
}

uint32_t shr(uint32_t n, uint32_t x){
  return(x >> n);
}

 
uint32_t sig0(uint32_t x){
  // See Sections 3.2 and 4.1.2 for definitions.	
  return(rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
}

uint32_t sig1(uint32_t x){
  // See Sections 3.2 and 4.1.2 for definitions.
  return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));
}

// see Section 4.1.2 for definitions.
uint32_t SIG0(uint32_t x){
  return (rotr(2, x) ^ rotr(13, x) ^ rotr(22, x));	
}

uint32_t SIG1(uint32_t x){
  return (rotr(6, x) ^ rotr(11, x) ^ rotr(25, x));	
}

// See Section 4.1.2 for definitions.
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
  return ((x & y) ^ ((!x) & z));	
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
  return ((x & y) ^ (x & z));	
}

int nextmsgblock(FILE *f, union msgblock *M, enum status *S, int *nobits);
  union msgblock M;

  uint64_t nobits = 0;

  uint64_t nobytes;

  enum status S = READ;

  int i;

  while (S == READ) {
    nobytes = fread(M.e, 1, 64, f);
    printf("Read %2llu bytes\n", nobytes);
    nobits = nobits + (nobytes * 8);
    if (nobytes < 56){
      printf("I've found a block with less than 55 bytes!\n");
      M.e[nobytes] = 0x80;
      while (nobytes < 56){
        nobytes = nobytes + 1;
