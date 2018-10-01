#ifndef __DA_INCLUDED__
#define __DA_INCLUDED__

#include <stdio.h>

typedef struct da DA;

//edit newDA for free function pointer

extern DA *newDA(void (*d)(FILE *,void *),void (*f)(void *)); //creates structure and uses function pointer to display value
extern void insertDA(DA *items,void *value);  //adds the value to the back of the array
extern void *removeDA(DA *items); //removes the last item from the array
extern void unionDA(DA *recipient,DA *donor); //appends the second array to the first
extern void *getDA(DA *items,int index);  //returns the value located at items[index]
extern void *setDA(DA *items,int index,void *value);  //sets the value at items[index] to passed parameter
extern void **extractDA(DA *items); //returns the underlying structure
extern int sizeDA(DA *items); //returns the number of items stored in array
extern void visualizeDA(FILE *fp,DA *items);  //print array enclosed in [] and prints open slots
extern void displayDA(FILE *fp,DA *items);  //print the items stored in the array
extern void freeDA(DA *items);	//frees the objects stored and DA object

#endif
