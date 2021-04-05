#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "list.h"

#define BUFFER_SIZE 2
/*
  gcc -g -o jabber jabber.c list.c
  ./jabber bit-wright.txt zap-wright.txt
*/

char *getBits(FILE *);
void jabber(char *, FILE *);
char* substr(const char *, int, int);
void intToBinary(int, int, FILE *);

int main(int argc, char *argv[] ) {
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

  char *input = getBits(ifp);
  fclose(ifp);
  jabber(input, ofp);
  fclose(ofp);
}

char *getBits(FILE * ifp) {
  char letter;
  int x=0, size = BUFFER_SIZE;
  char *buffer_;
  buffer_= malloc(BUFFER_SIZE*sizeof(char));
  while(!feof(ifp)){
    letter = fgetc(ifp);
    if(letter == EOF) break;
		if(x>=size-1) {
			buffer_ = (char *)realloc(buffer_,size=2*size);
		}
		buffer_[x++] = letter;
	}
	buffer_[x] = '\0';
	return buffer_;
}

void jabber(char *input,FILE *ofp){
  int length = 0, currInput = 0, currTable = 0, lenChange = 2;
  list *start, *current;
  start = make_node("");
  current = start;
  while(input[currInput] != '\0') {
    int mLen = -1, mIndex = -1;
    list *tmp = start->next, *mNode = NULL;
    if(current != start) {
      //for loop to find prefix
      for(int x=1; x<=currTable; x++) {
        if(strcmp(tmp->word,substr(input, currInput, (currInput+strlen(tmp->word)))) == 0 && (strlen(tmp->word) > mLen || (strlen(tmp->word) == 1 &&  mLen == -1)) ) {
          mLen = strlen(tmp->word);
          mIndex = x;
          if(mNode != NULL)
              free_node(mNode);
          mNode = make_node(tmp->word);
        }
        tmp = tmp->next;
      }
    }
    /*write index of prefix, get and write next bit, make new prefix,
    and advance currInput*/
    if(mLen != -1 &&  mIndex != 0) {
      // write prefix index in length bits
      if(length > 0) {
        intToBinary(mIndex, length, ofp);
      }
      currInput += strlen(mNode->word);
    } else {
        for(int x = 0; x<length; x++)
          fprintf(ofp, "0");
    }
    char nextBit[1];
    nextBit[0] = input[currInput];
    currInput++;
    fprintf(ofp, "%c", nextBit[0]);
    if(mNode != NULL) {
      current->next = make_node(strcat(mNode->word, nextBit));
    } else {
      current->next = make_node(nextBit);
    }
    current = current->next;
    currTable++;
    free_node(mNode);
    if(length<2) {
      length++;
    } else if(currTable%lenChange == 0) {
      length++;
      lenChange *= 2;
    }
  }
}

char* substr(const char *src, int start, int end) {
	int len = end - start;
	char *dest = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = start; i < end && (*(src + i) != '\0'); i++) {
		*dest = *(src + i);
		dest++;
	}
	*dest = '\0';
	return dest - len;
}

void intToBinary(int num, int length, FILE * ofp) {
  int bin[length];
  for(int x = 0; x<length; x++)
    bin[x] = 0;
  for(int x=0; num>0;x++) {
    bin[x] = num%2;
    num /= 2;
  }
  for(int x=length-1; x>=0; x--) {
      fprintf(ofp, "%d", bin[x]);
  }
}
