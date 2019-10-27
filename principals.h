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

struct title_principals *get_principals(const char *directory);
