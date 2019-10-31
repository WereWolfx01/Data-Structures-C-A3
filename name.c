#include "name.h"

struct name_arrayStruct *get_name(const char *directory){
  char *path, *columnData;
  char *buffer, *bufferPointer, *nconstBuffer, *primaryNameBuffer;
  int count, i;
  struct name_basics *namesArray;
  struct name_arrayStruct *arrayHolder;
  FILE *fp;

  path = NULL;
  columnData = NULL;
  buffer = NULL;
  nconstBuffer = NULL;
  primaryNameBuffer = NULL;
  count = 0;
  i = 0;
  buffer = malloc(1024);
  arrayHolder = malloc( sizeof(struct name_arrayStruct) );

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

  arrayHolder->numElements = count;
  arrayHolder->arrayPtr = namesArray;
  arrayHolder->nconstTree = NULL;
  arrayHolder->nameTree = NULL;

  free(buffer);
  free(fp);
  return arrayHolder;
}

void build_nameTree(struct name_arrayStruct *holder){
  int i;

  for( i=0; i<(holder->numElements); i++ ){
    add_node( &(holder->nameTree), &((holder->arrayPtr)[i].primaryName), &((holder->arrayPtr)[i]) );
  }
}

struct name_basics *find_primary_name(struct name_arrayStruct *holder, char *toFind){
  struct name_basics *nameFound;
  struct tree *node;

  node = find_node( holder->nameTree, toFind );

  if( node == NULL ){
    return NULL;
  }
  else{
    nameFound = (struct name_basics *) node->data;
  }
  return nameFound;
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
