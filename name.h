#include "common.h"
#include "binary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct name_basics
{
  char *nconst;
  char *primaryName;
};

struct name_arrayStruct
{
    struct name_basics *arrayPtr;
    int numElements;
    struct tree *nconstTree, *nameTree;
};

struct name_arrayStruct *get_name(const char *directory);
void build_nameTree(struct name_arrayStruct *holder);
struct name_basics *find_primary_name(struct name_arrayStruct *holder, char *toFind);
void build_nconstTree(struct name_arrayStruct *holder);
struct name_basics *find_nconst(struct name_arrayStruct *holder, char *toFind);



void freeName(struct name_basics *toFree);
void freeNameArray(struct name_basics **toFree);
