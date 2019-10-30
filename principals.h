#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct title_principals
{
  char *tconst;
  char *nconst;
  char *characters;
};

struct principals_arrayStruct
{
    struct title_principals *arrayPtr;
    int numElements;
    struct tree *tconstTree, *nconstTree;
};

struct principals_arrayStruct *get_principals(const char *directory);
