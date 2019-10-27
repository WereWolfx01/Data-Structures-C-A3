#include "principals.h"

struct title_principals *get_principals(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *tconstBuffer, *nconstBuffer, *charactersBuffer;
  struct title_principals *principalsArray;
  int count, i;
  FILE *fp;

  path = NULL;
  buffer = NULL;
  bufferPointer = NULL;
  columnData = NULL;
  tconstBuffer = NULL;
  nconstBuffer = NULL;
  charactersBuffer = NULL;
  count = 0;
  i = 0;

  buffer = malloc(1024);
  path = malloc(strlen(directory) + 22); /* 21 -> /title.principals.tsv and 1 -> \0 */
  strcpy(path, directory);
  strcat(path, "/title.principals.tsv");
  printf("path = %s\n", path);
  fp = fopen(path, "r");
  free(path);

  if( fp == NULL ){
    perror("Error: ");
    return NULL;
  }

  while( !feof(fp) ){
    fgets(buffer, 1024, fp);
    bufferPointer = buffer;
    if(count > 14627307){
      printf("%s\n", buffer);
    }

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 3);

    if( strstr(columnData, "actor") || strstr(columnData, "actress") ){
      count++;
    }

    free(columnData);

  }
  printf("lines = %d\n", count);

  principalsArray = malloc( sizeof(struct title_principals) * count );
  fseek(fp, 0, SEEK_SET);

  while( !feof(fp) ){
    fgets(buffer, 1024, fp);
    bufferPointer = buffer;

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 3);

    if( strstr(columnData, "actor") || strstr(columnData, "actress") ){
      get_column(bufferPointer, &tconstBuffer, 0);
      principalsArray[i].tconst = duplicateString(tconstBuffer);
      free(tconstBuffer);
      get_column(bufferPointer, &nconstBuffer, 2);
      principalsArray[i].nconst = duplicateString(nconstBuffer);
      free(nconstBuffer);
      get_column(bufferPointer, &charactersBuffer, 5);
      principalsArray[i].characters = duplicateString(charactersBuffer);
      free(charactersBuffer);
      i++;
    }
    free(columnData);
  }


  free(buffer);
  free(fp);

  return principalsArray;
}
