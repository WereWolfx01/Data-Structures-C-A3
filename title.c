#include "title.h"

struct title_basics *get_title(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *tconstBuffer, *primaryTitleBuffer;
  struct title_basics *titlesArray;
  int count, i;
  FILE *fp;

  path = NULL;
  buffer = NULL;
  bufferPointer = NULL;
  columnData = NULL;
  tconstBuffer = NULL;
  primaryTitleBuffer = NULL;
  count = 0;
  i = 0;

  buffer = malloc(1024);
  path = malloc(strlen(directory) + 18); /* 17 -> /title.basics.tsv and 1 -> \0 */
  strcpy(path, directory);
  strcat(path, "/title.basics.tsv");
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

    get_column(bufferPointer, &columnData, 1);

    if( strstr(columnData, "movie") ){
      free(columnData);
      get_column(bufferPointer, &columnData, 4);
      if( strstr(columnData, "0") ){
        count++;
      }
      free(columnData);
    }
    else{
      free(columnData);
    }

  }
  printf("lines = %d\n", count);

  titlesArray = malloc( sizeof(struct title_basics) * count );
  fseek(fp, 0, SEEK_SET);

  while( fgets(buffer, 1024, fp) ){
    bufferPointer = buffer;

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 1);

    if( strstr(columnData, "movie") ){
      free(columnData);
      get_column(bufferPointer, &columnData, 4);
      if( strstr(columnData, "0") ){
        get_column(bufferPointer, &tconstBuffer, 0);
        titlesArray[i].tconst = duplicateString(tconstBuffer);
        free(tconstBuffer);
        get_column(bufferPointer, &primaryTitleBuffer, 2);
        titlesArray[i].primaryTitle = duplicateString(primaryTitleBuffer);
        free(primaryTitleBuffer);
        i++;
      }
      free(columnData);
    }
    else{
      free(columnData);
    }

  }


  free(buffer);
  free(fp);

  return titlesArray;
}
