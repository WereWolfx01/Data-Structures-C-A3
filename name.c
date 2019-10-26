#include "name.h"



struct name_basics *get_name(const char *directory){
  char *path, *columnData;
  char *buffer, *nconstBuffer, *primaryNameBuffer;
  int count, i;
  struct name_basics *namesArray;
  FILE *fp;

  path = NULL;
  columnData = NULL;
  buffer = NULL;
  count = 0;
  i = 0;
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
    fgets(buffer, 256, fp);

    if( buffer == NULL ){
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

    free(columnData);
  }
  printf("lines = %d\n", count);

  namesArray = malloc( sizeof(struct name_basics) * count );
  fseek(fp, 0, SEEK_SET);

  while( !feof(fp) ){
    fgets(buffer, 256, fp);

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(buffer, &columnData, 4);

    if( strstr(columnData, "actor") ){
      get_column(buffer, &nconstBuffer, 0);
      namesArray[i].nconst = strdup(nconstBuffer);
      free(nconstBuffer);
      get_column(buffer, &primaryNameBuffer, 1);
      namesArray[i].primaryName = strdup(primaryNameBuffer);
      free(primaryNameBuffer);
      i++;
    }

    else if( strstr(columnData, "actress") ){
      get_column(buffer, &nconstBuffer, 0);
      namesArray[i].nconst = strdup(nconstBuffer);
      free(nconstBuffer);
      get_column(buffer, &primaryNameBuffer, 1);
      namesArray[i].primaryName = strdup(primaryNameBuffer);
      free(primaryNameBuffer);
      i++;
    }

    free(columnData);
  };
  free(fp);
  return namesArray;
}
