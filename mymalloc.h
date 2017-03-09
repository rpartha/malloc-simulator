//Ramaseshan Parthasarathy
//Nishanth Athreya

#ifndef __mymalloc_H__
#define __mymalloc_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_SIZE 5000
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

typedef struct MyMetaData{
	struct MyMetaData *prev, *next; //pointers to previous and next nodes
	//unsigned int prev:13;
	//unsigned int next:13;
	unsigned int occupied:1; //is the space free or not?
	unsigned int memsize:24; //define size of meta data (memory block) to be 24 bits = 3 bytes
}MyMetaData;

void *mymalloc(unsigned int size, char *file, unsigned int line);
void myfree(void* inputPtr, char *file, unsigned int line);
void combinefree(MyMetaData *n); 

#endif
