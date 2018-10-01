#include <stdio.h>

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

typedef struct string STRING;

extern STRING *newSTRING(char*);  //returns structure wrapping the value
extern char* getSTRING(STRING *); //returns the value stored in the structure
extern char* setSTRING(STRING *,char*); //sets the value stored in the structure parameter
extern void displaySTRING(FILE *,void *); //displays the wrappped value to the FILE*
extern int compareSTRING(void *,void *);  //returns the first value minus the second
extern void freeSTRING(void *); //frees the memory allocated by newSTRING


#endif
