/*#include "common.h"
#include "binary.h"

"
#include "title.h"*/
#include "stdio.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char const *argv[]) {
  struct name_arrayStruct *name_basics;
  struct name_basics *name;
  /*struct title_arrayStruct *title_basics;
  struct title_basics *title;*/
  /*struct principals_arrayStruct *principals;
  int i;*/

  if( argc < 2 ){
    fprintf(stderr, "Usage: %s directory\n", argv[0]);
    return -1;
  }

  /*names = get_name(argv[1]);
  printf("line 1 nconst = %s primaryName = %s\n", (names->arrayPtr)[0].nconst, (names->arrayPtr)[0].primaryName);
  printf("line 6 nconst = %s primaryName = %s\n", (names->arrayPtr)[5].nconst, (names->arrayPtr)[5].primaryName);
  printf("line 16666 nconst = %s primaryName = %s\n", (names->arrayPtr)[16665].nconst, (names->arrayPtr)[16665].primaryName);
  printf("line 3722708 nconst = %s primaryName = %s\n", (names->arrayPtr)[3722707].nconst, (names->arrayPtr)[3722707].primaryName);*/
  name_basics = get_name(argv[1]);
  build_nameTree(name_basics);
  name = find_primary_name(name_basics, "Anthony Daniels");
  printf( "%p\n", (void *)name );

  printf( "%s\n", name->nconst );

  printf( "%s\n", name->primaryName );

  /*title_basics = get_title(argv[1]);
  build_titleTree(title_basics);
  title = find_primary_title(title_basics, "Star Wars: Episode V - The Empire Strikes Back");*/

  /*printf( "%p\n", (void *)title );

  printf( "%s\n", title->tconst );

  printf( "%s\n", title->primaryTitle );*/

  /*printf("%d\n", titles->numElements);

  for( i=0; i<10; i++ ){
    printf("%s %s\n", (titles->arrayPtr)[i].tconst, (titles->arrayPtr)[i].primaryTitle);
  }
  printf("\n");
  for (i=524619;i<524629;i++){
    printf( "%s %s\n", (titles->arrayPtr)[i].tconst, (titles->arrayPtr)[i].primaryTitle );
  }*/

  /*printf( "%p\n", (void *)(title_basics->titleTree) );

  printf( "%s\n", (title_basics->titleTree)->key );

  printf( "%p\n", (void *)(title_basics->titleTree)->data );

  printf( "%s\n", ((struct title_basics *)((title_basics->titleTree)->data))->primaryTitle );

  printf( "%s\n", ((struct title_basics *)((title_basics->titleTree)->data))->tconst );*/



  /*principals = get_principals(argv[1]);*/

  /*for (i=0;i<10;i++){
    printf( "%s %s %s\n", (principals->arrayPtr)[i].tconst,
                          (principals->arrayPtr)[i].nconst,
                          (principals->arrayPtr)[i].characters );
  }
  printf( "\n" );
  for (i=14627307;i<14627317;i++){
    printf( "%s %s %s\n", (principals->arrayPtr)[i].tconst,
                          (principals->arrayPtr)[i].nconst,
                          (principals->arrayPtr)[i].characters );
  }*/

  return 0;
}
