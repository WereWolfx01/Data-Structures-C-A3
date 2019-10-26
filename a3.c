#include "common.h"
#include "binary.h"
#include "name.h"
#include "principals.h"
#include "title.h"
#include "stdio.h"


int main(int argc, char const *argv[]) {
  struct name_basics *names;

  if( argc < 2 ){
    fprintf(stderr, "Usage: %s directory\n", argv[0]);
    return -1;
  }

  names = get_name(argv[1]);
  /*printf("line 1 nconst = %s primaryName = %s\n", names[0]->nconst, names[0]->primaryName);
  printf("line 6 nconst = %s primaryName = %s\n", names[5]->nconst, names[5]->primaryName);
  printf("line 16666 nconst = %s primaryName = %s\n", names[16665]->nconst, names[16665]->primaryName);
  printf("line 3722708 nconst = %s primaryName = %s\n", names[3722707]->nconst, names[3722707]->primaryName);*/

  return 0;
}
