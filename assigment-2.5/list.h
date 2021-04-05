#ifndef LIST_H
#define LIST_H

typedef struct list_s {
    char *word;
    struct list_s *next;
} list;

list *make_node(char *);
void free_node(list *);
void show(list *);

#endif
