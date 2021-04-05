#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
#include "list.h"

list *make_node(char *str) {
    list *ptr;
    ptr = (list *)malloc(sizeof(list));
    assert(ptr != NULL);
    ptr->word = (char *)strdup(str);
    ptr->next = NULL;
    return ptr;
}

void free_node(list *ptr) {
    free(ptr);
}

void show(list *start) {
	list *ptr;
	
	for(ptr = start; ptr != NULL; ptr=ptr->next) {
		fprintf(stderr,"[%s]\n",ptr->word);
	}
}
