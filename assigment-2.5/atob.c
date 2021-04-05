#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
/*gcc -g -o atob atob.c
./atob wright.txt bit-wright.txt */
void charToBinary(char c, int bin[]);

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

  char letter;
  while(!feof(ifp)) {
    letter = fgetc(ifp);
    if((int)letter != 10 && (int)letter > 0) {
      int bin[7];
      charToBinary(letter,bin);
      int tmp = 0;
      fprintf(ofp, "%d", tmp);
      if((int)letter <= 63) {
        fprintf(ofp, "%d", tmp);
        for(int y=5; y>=0; y--) {
          fprintf(ofp, "%d", bin[y]);
        }
      } else {
        for(int y=6; y>=0; y--) {
          fprintf(ofp, "%d", bin[y]);
        }
      }
      //fprintf(ofp, "\n");
    } else if((int)letter > 0){
      fprintf(ofp, "00001010");
    }
  }
  fclose(ifp);
  fclose(ofp);
//line 36 67


}

void charToBinary(char c, int bin[]) {
  int x = (int)c;
  for(int i=0; x>0;i++) {
    bin[i] = x%2;
    x /= 2;
  }
}
