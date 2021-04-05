#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
/*gcc -g -o btoa btoa.c -lm
./btoa bit-wright.txt ascii-wright.txt */
char binaryToChar(int n);

int main(int argc, char const *argv[]) {
  FILE *ifp, *ofp;

  if (argc < 3) {
    fprintf(stderr,"Not enough arguments\n");
    exit(1);
  }
  if (!(ifp = fopen(argv[1],"r"))) {
    fprintf(stderr,"Cannot open file %s\n",argv[1]);
    exit(1);
  }
  if (!(ofp = fopen(argv[2],"w"))) {
    fprintf(stderr,"Cannot open file %s\n",argv[2]);
    exit(1);
  }

  while(!feof(ifp)) {
    char letter;
    char bin[8];
    for(int x=0; x<8;x++) {
      bin[x]=fgetc(ifp);
    }
    if(strlen(bin) != 0)
      fprintf(ofp, "%c",binaryToChar(atoi(bin)));
  }
}

char binaryToChar(int n) {
  int dec = 0, i = 0, rem;
  while (n != 0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return (char)dec;
}
