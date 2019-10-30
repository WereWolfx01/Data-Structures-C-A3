#include "binary.h"

void add_node(struct tree **root, char **newKey, void *newValue){

  if(*root){ /*there is a node*/
    if( strcmp(*newKey, (*root)->key) < 0 ){ /*new key is less than current key*/
      add_node( &((*root)->children[0]), newKey, newValue );
    }
    else{ /*new key is greater or equal to current key*/
      add_node( &((*root)->children[1]), newKey, newValue );
    }
  }
  else{ /*root is empty*/
    *root = malloc( sizeof(struct tree) );
    (*root)->key = *newKey;
    (*root)->data = newValue;
    (*root)->children[0] = NULL;
    (*root)->children[1] = NULL;
  }


}
