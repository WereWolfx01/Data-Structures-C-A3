#include "name.h"



struct name_basics *get_name(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *nconstBuffer, *primaryNameBuffer;
  int count, i;
  struct name_basics *namesArray;
  FILE *fp;

  path = NULL;
  columnData = NULL;
  buffer = NULL;
  nconstBuffer = NULL;
  primaryNameBuffer = NULL;
  count = 0;
  i = 0;
  buffer = malloc(1024);

  path = malloc(strlen(directory) + 17); /* 16 -> /name.basics.tsv and 1 -> \0 */
  strcpy(path, directory);
  strcat(path, "/name.basics.tsv");
  printf("path = %s\n", path);
  fp = fopen(path, "r");
  free(path);

  if( fp == NULL ){
    perror("Error: ");
    return NULL;
  }

  while( fgets(buffer, 1024, fp) ){
    bufferPointer = buffer;

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 4);

    if( strstr(columnData, "actor") || strstr(columnData, "actress") ){
      count++;
    }

    free(columnData);
  }
  printf("lines = %d\n", count);

  namesArray = malloc( sizeof(struct name_basics) * count );
  fseek(fp, 0, SEEK_SET);

  while( fgets(buffer, 256, fp) ){
    bufferPointer = buffer;

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 4);

    if( strstr(columnData, "actor") || strstr(columnData, "actress") ){
      get_column(bufferPointer, &nconstBuffer, 0);
      namesArray[i].nconst = duplicateString(nconstBuffer);
      free(nconstBuffer);
      get_column(bufferPointer, &primaryNameBuffer, 1);
      namesArray[i].primaryName = duplicateString(primaryNameBuffer);
      free(primaryNameBuffer);
      i++;
    }

    free(columnData);
  }

  free(buffer);
  free(fp);
  return namesArray;
}

void freeName(struct name_basics toFree){ /*needs fix*/
  free(toFree.nconst);
  free(toFree.primaryName);
}

void freeNameArray(struct name_basics *toFree){ /*needs fix*/
  struct name_basics *pointer, *start;
  start = toFree;
  pointer = toFree;
  while( toFree ){
    toFree++;
    freeName(*pointer);
    pointer = toFree;
  }
  free(start);
}
