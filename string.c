#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

struct string{
  char* value;
};

STRING *newSTRING(char *x){
  STRING *p = malloc(sizeof(STRING));
  p->value = malloc((strlen(x) * sizeof(char)) + 1);
  if (p == 0){
      fprintf(stderr,"out of memory\n");
      exit(-1);
  }
  strcpy(p->value,x);
  return p;
}

char* getSTRING(STRING *str){
  return str->value;
}

char* setSTRING(STRING *str,char* x){
  char *old = str->value;
  strcpy(str->value,x);
  return old;
}

void displaySTRING(FILE *fp,void *x){
  fprintf(fp,"%s",getSTRING(x));
}

int compareSTRING(void *a,void *b){
  return strcmp(getSTRING(a),getSTRING(b));
}

void freeSTRING(void *x){
	STRING *temp = x;
	free(temp->value);
	free(temp);
}
