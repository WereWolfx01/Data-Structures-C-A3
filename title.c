/*
Aeman Abdulmuhssen
ID: 1003984
E-MAIL: aabdulmu@uoguelph.ca
*/

#include "title.h"

struct title_arrayStruct *get_title(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *tconstBuffer, *primaryTitleBuffer;
  struct title_basics *titlesArray;
  struct title_arrayStruct *arrayHolder;
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
  arrayHolder = malloc( sizeof(struct title_arrayStruct) );

  buffer = malloc(1024);
  path = malloc(strlen(directory) + 18); /* 17 -> /title.basics.tsv and 1 -> \0 */
  strcpy(path, directory);
  strcat(path, "/title.basics.tsv");
  /*printf("path = %s\n", path);*/
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
  /*printf("lines = %d\n", count);*/

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
        reverse( &(titlesArray[i].tconst) );
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

  arrayHolder->numElements = count;
  arrayHolder->arrayPtr = titlesArray;
  arrayHolder->tconstTree = NULL;
  arrayHolder->titleTree = NULL;

  free(buffer);
  fclose(fp);

  return arrayHolder;
}

void build_titleTree(struct title_arrayStruct *holder){
  int i;

  for( i=0; i<(holder->numElements); i++ ){
    add_node( &(holder->titleTree), &((holder->arrayPtr)[i].primaryTitle), &((holder->arrayPtr)[i]) );
  }

}

struct title_basics *find_primary_title(struct title_arrayStruct *holder, char *toFind){
  struct title_basics *titleFound;
  struct tree *node;

  node = find_node( holder->titleTree, toFind );

  if( node == NULL ){
    return NULL;
  }
  else{
    titleFound = (struct title_basics *) node->data;
  }
  return titleFound;

}

void build_tconstTree(struct title_arrayStruct *holder){
  int i;

  for( i=0; i<(holder->numElements); i++ ){
    add_node( &(holder->tconstTree), &((holder->arrayPtr)[i].tconst), &((holder->arrayPtr)[i]) );
  }
}

struct title_basics *find_tconst(struct title_arrayStruct *holder, char *toFind){
  struct title_basics *tconstFound;
  struct tree *node;

  node = find_node( holder->tconstTree, toFind );

  if( node == NULL ){
    return NULL;
  }
  else{
    tconstFound = (struct title_basics *) node->data;
  }
  return tconstFound;
}
