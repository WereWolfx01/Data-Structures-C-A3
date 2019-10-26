#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct name_basics
{
  char *nconst;
  char *primaryName;
};

struct name_basics *get_name(const char *directory);
