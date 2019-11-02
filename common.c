#include "common.h"

void get_column(char *line, char **new, int colNum){
  int i, tabCount, prevTab, nextTab, index;
  tabCount = 0;
  i = 0;
  prevTab = 0;
  nextTab = 0;

  while(*line){

    if( (*line == '\t') || (*line == '\n') ){
      nextTab = i;
      tabCount++;
      if(tabCount == colNum+1){
        break;
      }
      else{
        prevTab = nextTab+1;
      }
    }
    i++;
    line++;
  }
  index = nextTab - prevTab;
  *new = malloc( index + 1 );
  strncpy(*new, line - index, index);
  *((*new)+index) = '\0';

}

char *duplicateString(char *string){ /*my own function of strdup since strdup will not compile*/
  char *newString = NULL;

  newString = malloc(strlen(string) + 1);
  strcpy(newString, string);
  *(newString+strlen(string)) = '\0';

  return newString;
}

void reverse(char **string){
  int last, first;
  char temp;

  if( *string == NULL ){
    return;
  }

  last = strlen(*string) - 1;
  first = 0;
  while( first < last ){
    temp = *((*string)+first);
    *((*string)+first) = *((*string)+last);
    *((*string)+last) = temp;
    first++;
    last--;
  }

}
