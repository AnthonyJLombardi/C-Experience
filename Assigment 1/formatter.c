/*----------------------------------------------------------------------
 * formatter.c:
 *
 * compilation:
 *  gcc -g -o formatter formatter.c list.c
 * usage:
 *  ./formatter <input-file> <output-file> <width>
 *
 *-----------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

#define BUFFER_SIZE 2

void formatter( FILE *, FILE *, int );
char *getword(FILE *);
void free_list(list *);

int main( int argc, char *argv[] ) {
    FILE *ifp, *ofp;
    clock_t begin_time, end_time;
    double time_used;


    if (argc < 4) {
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

    begin_time = clock();
    formatter( ifp, ofp, atoi(argv[3]));
    end_time = clock();
    time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
    fprintf( stderr, "Time usage = %17.13f\n", time_used );

    fclose(ifp);
    fclose(ofp);
}

void formatter( FILE *ifp, FILE *ofp, int width ) {
	char *word;
	list *start, *current;
	//reading in words from file
	start = NULL;
	while(!feof(ifp)){
		word = getword(ifp);
    if(strlen(word) != 0) {
      //fprintf(stderr, "{%s}",word );
		    if(start != NULL) {
			       current->next = make_node(word);
             current = current->next;
        } else {
              start = make_node(word);
			        current = start;
		    }
    }
		free(word);
  }
  list *lineStart=NULL, *lineCurr, *bigStart=0, *bigCurr;
  int curWidth=0, lineWords=0;
  current = start;
  while(current != NULL) {
    if(curWidth < width && strlen(current->word)<=(width-curWidth)) {
      //checks to see if the next word will fit on the current line
      if(lineStart != NULL) {
        lineCurr->next = make_node(current->word);
        lineCurr = lineCurr->next;
      } else {
        lineStart = make_node(current->word);
        lineCurr = lineStart;
      }
      curWidth +=strlen(lineCurr->word);
      //takes a space into account will be removed later
      curWidth++;
      current = current->next;
      lineWords++;
    } else if(strlen(current->word) > width) {
      //checks if word is too big to fit on line
      if(bigStart != NULL) {
        bigCurr->next = make_node(current->word);
        bigCurr = bigCurr->next;
      } else {
        bigStart = make_node(current->word);
        bigCurr = bigStart;
      }
      current = current->next;
    } else {
      //removes spaces accounted for while adding words
      curWidth -= (lineWords);
      //finds number of spaces between each words
      int spaces=0;
      if(lineWords != 1)
        spaces=(width - curWidth)/(lineWords-1);
      else
        spaces=(width - curWidth);
      /*adds the total number of spaces to curWidth to see
      if anymore need to be added*/
      curWidth += spaces*(lineWords-1);
      int offset=0;
      if(curWidth != width)
        offset = width-curWidth;
      lineCurr = lineStart;
      while(lineCurr->next != NULL) {
        fprintf(ofp, "%s", lineCurr->word);
        for(int x=0; x<spaces; x++)
          fprintf(ofp, " ");
        if(offset !=0) {
          fprintf(ofp, " ");
          offset --;
        }
        lineCurr = lineCurr->next;
      }
      fprintf(ofp, "%s\n", lineCurr->word);

      //resets variables for next line
      curWidth=0;lineWords=0;
      free_list(lineStart);
      lineCurr = NULL;
      lineStart = NULL;
    }
  }
  // prints last line
  if(lineStart != NULL) {
    lineCurr = lineStart;
    while(lineCurr != NULL) {
      fprintf(ofp, "%s ", lineCurr->word);
      lineCurr = lineCurr->next;
    }
    fprintf(ofp, "\n");
  }
  //prints any words that are bigger thean the width
  if(bigStart != NULL) {
    fprintf(ofp, "Word(s) bigger than %d charaters:\n",width);
    bigCurr = bigStart;
    while(bigCurr != NULL) {
      fprintf(ofp, "[%s] ", bigCurr->word);
      bigCurr = bigCurr->next;
    }
    fprintf(ofp, "\n");
  }
  free_list(lineStart);
  free_list(bigStart);
  free_list(start);
}

char *getword(FILE *ifp) {
	char letter;
	int x=0;
	int size = BUFFER_SIZE;
	char *buffer_;
	buffer_= malloc(BUFFER_SIZE*sizeof(char));
	while(!isspace(letter = fgetc(ifp))) {
		if(letter == EOF) break;
		if(x>size-1) {
			buffer_ = (char *)realloc(buffer_,size=2*size);
		}
		buffer_[x++] = letter;
	}
	buffer_[x] = '\0';
	return buffer_;
}

void free_list(list *start) {
  list* tmp=NULL;
  while(start != NULL) {
    tmp = start;
    start = start->next;
    free_node(tmp);
  }
  start = NULL;
}
