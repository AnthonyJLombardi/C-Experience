#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "list.h"

#define BUFFER_SIZE 2
/*
  gcc -g -o wocky wocky.c list.c -lm
  ./wocky zap-wright.txt kapow-wright.txt
*/

char *getBits(FILE *);
void wocky(char *, FILE *);
int binaryToInt(char *, int length);


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
  wocky(input, ofp);
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

void wocky(char *input,FILE *ofp){
  int length = 0, currInput = 0, currTable = 0, lenChange = 2;
  list *start, *current;
  start = make_node("");
  current = start;
  while(input[currInput] != '\0') {
    /*reads in index, prints prefix from table, gets the next bit,
    prints nextbit, and concantionas it onto the prefix and addes a new
    prefix to the table*/
    list *prefix = NULL;
    if(length>0) {
      char index[length];
      for(int x=0; x<length;x++) {
        index[x] = input[currInput+x];
      }
      currInput+=length;
      int tmp = binaryToInt(index, length);
      if(tmp>0) {
        list *loopNode = start->next;
        for(int x=1; x<=tmp; x++) {
          if(x == tmp)
            prefix = make_node(loopNode->word);
          loopNode = loopNode->next;
        }
        fprintf(ofp, "%s", prefix->word);
      } else if(tmp == 0 && length != 1) {
        for(int x=0; x<length; x++) {
          fprintf(ofp, "0");
        }
      }
    }
    char nextBit[1];
    nextBit[0] = input[currInput];
    currInput++;
    fprintf(ofp, "%c", nextBit[0]);
    //add nextBit to prefix and add new item to table
    if(prefix != NULL) {
      current->next = make_node(strcat(prefix->word, nextBit));
    } else {
      current->next = make_node(nextBit);
    }
    current = current->next;
    currTable++;
    free_node(prefix);
    if(length<2) {
      length++;
    } else if(currTable%lenChange == 0) {
      length++;
      lenChange *= 2;
    }
  }
}

int binaryToInt(char *index, int length) {
  int start = pow(2,length)/2,num=0;
  for(int x=0; x<length; x++) {
    if(index[x] == '1')
      num+=start;
    start /=2;
  }
  return num;
}
