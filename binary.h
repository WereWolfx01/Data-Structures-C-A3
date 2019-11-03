/*
Aeman Abdulmuhssen
ID: 1003984
E-MAIL: aabdulmu@uoguelph.ca
*/

#ifndef BINARY
#define BINARY

#include "string.h"
#include "stdlib.h"


struct tree{
  char *key;
  void *data;
  struct tree *children[2];
};

void add_node(struct tree **root, char **newKey, void *newValue);
void *find_node(struct tree *root, char *toFind);
void free_tree(struct tree **toFree);

#endif
