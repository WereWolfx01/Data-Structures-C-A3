#include "common.h"
#include "binary.h"
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
void build_nconstTree_p(struct principals_arrayStruct *holder);
void build_tconstTree_p(struct principals_arrayStruct *holder);
struct title_principals *find_nconst_p(struct principals_arrayStruct *holder, char *toFind);
struct tree *find_nconst_p_modified(struct principals_arrayStruct *holder, char *toFind);
struct title_principals *find_tconst_p(struct principals_arrayStruct *holder, char *toFind);
