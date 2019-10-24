#include "name.h"

struct name_basics *get_name(const char *directory){
  char *path;
  char buffer[256];
  FILE *fp;

  path = malloc(strlen(directory) + 17); /* 16 -> /name.basics.tsv and 1 -> \0 */
  strcpy(path, directory);
  strcat(path, "/name.basics.tsv");
  printf("path = %s\n", path);
  fp = fopen(path, "r");
  if( fp == NULL ){
    perror("Error: ");
    return NULL;
  }
  while( !feof(fp) ){
    printf("test\n");
    if( fgets(buffer, 256, fp) == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }
    printf("%s\n", buffer);

  }

  return NULL;
}
