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
  struct tree *node;

  char *buffer, *command, *end, *key;
  int choice = 0;

  if( argc < 2 ){
    fprintf(stderr, "Usage: %s directory\n", argv[0]);
    return -1;
  }

  /*
  * Building arrays
  */
  /*printf("getting name\n");*/
  name_basics = get_name( argv[1] );
  /*printf("getting title\n");*/
  title_basics = get_title( argv[1] );
  /*printf("getting principals\n");*/
  title_principals = get_principals( argv[1] );


  /*
  * Building trees
  */
  /*printf("building name tree\n");*/
  build_nameTree( name_basics );
  /*printf("building nconst tree\n");*/
  build_nconstTree( name_basics );

  /*printf("building title tree\n");*/
  build_titleTree( title_basics );
  /*printf("building tconst tree\n");*/
  build_tconstTree( title_basics );

  /*printf("building nconst tree\n");*/
  build_nconstTree_p( title_principals );
  /*printf("building tconst tree\n");*/
  build_tconstTree_p( title_principals );


  buffer = malloc(MAX);
  printf("> ");
  fgets(buffer, MAX, stdin);
  while( strncmp(buffer, "exit", 4) != 0 ){
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

    else if( strncmp(command, "title", 5) == 0 ){
      choice = 2;
    }

    else{
      choice = 0;
    }

    while( *command != ' '){ /*point to end of command*/
      command++;
    }

    key = command;
    while( *key == ' ' ){ /*eliminate any spaces between command and key*/
      key++;
    }

    if( choice == 1 || choice == 2 ){
      switch( choice ){
        case 1:
          name = find_primary_name(name_basics, key);
          if( name == NULL ){
            fprintf(stderr, "Name Not Found!\n");
            break;
          }
          node = find_nconst_p_modified(title_principals, name->nconst);
          while( node ){
            title = find_tconst( title_basics, ((struct title_principals *)node->data)->tconst );
            if( title != NULL ){
              printf("%s : %s\n", title->primaryTitle, ((struct title_principals *)node->data)->characters );
            }
            node = (struct tree *)find_node(node->children[1], name->nconst);
          }
          break;

        case 2:
          title = find_primary_title( title_basics, key );
          if( title == NULL ){
            fprintf(stderr, "Title Not Found!\n");
            break;
          }
          node = find_tconst_p_modified( title_principals, title->tconst );
          while( node ){
            name = find_nconst( name_basics, ((struct title_principals *)node->data)->nconst );
            if( name != NULL ){
              printf("%s : %s\n", name->primaryName, ((struct title_principals *)node->data)->characters );
            }
            node = (struct tree *)find_node(node->children[1], title->tconst);
          }
          break;

        default:
          fprintf(stderr, "Error\n");
          break;
      }
    }

    printf("> ");
    fgets(buffer, MAX, stdin);
  } /*Exit loop only when user types "exit"*/

  free( buffer );
  freeName( &name_basics );
  freeTitle( &title_basics );
  freePrinciples( &title_principals );

  return 0;
}
