#include "name.h"
#include "common.h"

struct name_basics *get_name(const char *directory){
  char *path, *columnData;
  char *buffer;
  int count = 0;
  FILE *fp;

  path = NULL;
  columnData = NULL;
  buffer = NULL;
  buffer = malloc(256);

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
    if( fgets(buffer, 256, fp) == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }
    get_column(buffer, &columnData, 4);
    if( strstr(columnData, "actor") ){
      count++;
    }
    else if( strstr(columnData, "actress") ){
      count++;
    }
  }
  printf("lines = %d\n", count);
  return NULL;
}
