#include "principals.h"

struct principals_arrayStruct *get_principals(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *tconstBuffer, *nconstBuffer, *charactersBuffer;
  struct title_principals *principalsArray;
  struct principals_arrayStruct *arrayHolder;
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

  arrayHolder = malloc( sizeof(struct principals_arrayStruct) );
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

  while( fgets(buffer, 1024, fp) ){
    bufferPointer = buffer;

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

  while( fgets(buffer, 1024, fp) ){
    bufferPointer = buffer;

    if( buffer == NULL ){
      fprintf(stderr, "Error reading file to buffer\n");
      break;
    }

    get_column(bufferPointer, &columnData, 3);

    if( strstr(columnData, "actor") || strstr(columnData, "actress") ){
      get_column(bufferPointer, &tconstBuffer, 0);
      principalsArray[i].tconst = duplicateString(tconstBuffer);
      reverse(&(principalsArray[i].tconst));
      free(tconstBuffer);
      get_column(bufferPointer, &nconstBuffer, 2);
      principalsArray[i].nconst = duplicateString(nconstBuffer);
      reverse(&(principalsArray[i].nconst));
      free(nconstBuffer);
      get_column(bufferPointer, &charactersBuffer, 5);
      principalsArray[i].characters = duplicateString(charactersBuffer);
      free(charactersBuffer);
      i++;
    }
    free(columnData);
  }

  arrayHolder->numElements = count;
  arrayHolder->arrayPtr = principalsArray;
  arrayHolder->tconstTree = NULL;
  arrayHolder->nconstTree = NULL;

  free(buffer);
  free(fp);

  return arrayHolder;
}

void build_nconstTree_p(struct principals_arrayStruct *holder){
  int i;

  for( i=0; i<(holder->numElements); i++ ){
    add_node( &(holder->nconstTree), &((holder->arrayPtr)[i].nconst), &((holder->arrayPtr)[i]) );
  }
}

void build_tconstTree_p(struct principals_arrayStruct *holder){
  int i;

  for( i=0; i<(holder->numElements); i++ ){
    add_node( &(holder->tconstTree), &((holder->arrayPtr)[i].tconst), &((holder->arrayPtr)[i]) );
  }
}

struct title_principals *find_nconst_p(struct principals_arrayStruct *holder, char *toFind){
  struct title_principals *nconstFound;
  struct tree *node;

  node = find_node( holder->nconstTree, toFind );

  if( node == NULL ){
    return NULL;
  }
  else{
    nconstFound = (struct title_principals *) node->data;
  }
  return nconstFound;
}

struct title_principals *find_tconst_p(struct principals_arrayStruct *holder, char *toFind){
  struct title_principals *tconstFound;
  struct tree *node;

  node = find_node( holder->tconstTree, toFind );

  if( node == NULL ){
    return NULL;
  }
  else{
    tconstFound = (struct title_principals *) node->data;
  }
  return tconstFound;
}
