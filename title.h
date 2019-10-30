#include "common.h"
#include "binary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct title_basics
{
  char *tconst;
  char *primaryTitle;
};

struct title_arrayStruct
{
    struct title_basics *arrayPtr;
    int numElements;
    struct tree *tconstTree, *titleTree;
};

struct title_arrayStruct *get_title(const char *directory);
void build_tindex(struct title_arrayStruct *holder);
