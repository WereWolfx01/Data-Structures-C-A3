#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct title_basics
{
  char *tconst;
  char *primaryTitle;
};

struct title_basics *get_title(const char *directory);
