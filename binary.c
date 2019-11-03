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
  else{ /*node is empty*/
    *root = malloc( sizeof(struct tree) );
    (*root)->key = *newKey;
    (*root)->data = newValue;
    (*root)->children[0] = NULL;
    (*root)->children[1] = NULL;
  }
}

void *find_node(struct tree *root, char *toFind){
  if(root){
    if( strcmp(toFind, root->key) == 0 ){
      return root;
    }
    else{
      if( strcmp(toFind, root->key) < 0 ){
        return find_node( root->children[0], toFind );
      }
      else{
        return find_node( root->children[1], toFind );
      }
    }
  }

  else{ /*no node found*/
    return NULL;
  }
}


void free_tree(struct tree **toFree){
  if( *toFree == NULL ){
    return;
  }

  free_tree( &((*toFree)->children[0]) );
  free_tree( &((*toFree)->children[1]) );

  free(*toFree);

}
