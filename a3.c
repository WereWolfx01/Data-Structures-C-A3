/*
Aeman Abdulmuhssen
ID: 1003984
E-MAIL: aabdulmu@uoguelph.ca
*/

#include "stdio.h"
#include "name.h"
#include "title.h"
#include "principals.h"

#define MAX 1024

int main(int argc, char const *argv[]) {
  struct name_arrayStruct *name_basics;
  struct title_arrayStruct *title_basics;
  struct principals_arrayStruct *title_principals;
  struct name_basics *name;
  struct title_basics *title;
  struct title_principals *principals;

  char *buffer, *command, *end, *key;
  int choice = 0;

  if( argc < 2 ){
    fprintf(stderr, "Usage: %s directory\n", argv[0]);
    return -1;
  }


  buffer = malloc(MAX);
  printf("> ");
  fgets(buffer, MAX, stdin);
  command = buffer;

  while( *command == ' '){ /*eliminate the leading white spaces*/
    command++;
  }

  end = buffer + strlen(buffer) - 2;
  while( *end == ' ' ){ /*eliminate the trailing white spaces*/
    end--;
  }
  *(end+1) = '\0';

  if( strncmp(command, "name", 4) == 0 ){
    choice = 1;
  }


  if( strncmp(command, "title", 5) == 0 ){
    choice = 2;
  }

  while( *command != ' '){ /*point to end of command*/
    command++;
  }

  key = command;
  while( *key == ' ' ){ /*eliminate any spaces between command and key*/
    key++;
  }


  /*
  * Building arrays
  */
  name_basics = get_name( argv[1] );
  title_basics = get_title( argv[1] );
  title_principals = get_principals( argv[1] );

  /*
  * Building trees
  */
  build_nameTree( name_basics );
  build_nconstTree( name_basics );

  build_titleTree( title_basics );
  build_tconstTree( title_basics );

  build_nconstTree_p( title_principals );
  build_tconstTree_p( title_principals );


  switch( choice ){
    case 1:
      name = find_primary_name(name_basics, key);
      if(  name == NULL ){
        fprintf(stderr, "name not found\n");
        exit(-1);
      }
      principals = find_nconst_p( title_principals, name->nconst );
      if(  principals == NULL ){
        fprintf(stderr, "principal not found\n");
        exit(-1);
      }
      title = find_tconst( title_basics, principals->tconst );
      if(  title == NULL ){
        fprintf(stderr, "title not found\n");
        exit(-1);
      }
      printf("%s : [\"%s\"]\n", title->primaryTitle, principals->characters );
      break;

    case 2:
      title = find_primary_title( title_basics, key );
      if(  title == NULL ){
        fprintf(stderr, "title not found\n");
        exit(-1);
      }
      principals = find_tconst_p( title_principals, title->tconst );
      if(  principals == NULL ){
        fprintf(stderr, "principal not found\n");
        exit(-1);
      }
      name = find_nconst( name_basics, principals->nconst );
      if(  name == NULL ){
        fprintf(stderr, "name not found\n");
        exit(-1);
      }
      printf("%s : [\"%s\"]\n", name->primaryName, principals->characters);
      break;

    default:
      fprintf(stderr, "command not found\n");
      break;
  }

  free(buffer);

  return 0;
}
