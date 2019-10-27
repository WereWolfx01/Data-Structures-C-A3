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
  
  return 0;
}
