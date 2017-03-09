//Ramaseshan Parthasarathy
//Nishanth Athreya

#include "mymalloc.h"

static char myblock[MY_SIZE]; //simulated main memory

static MyMetaData *root; //start of the [DOUBLY] linked list

MyMetaData *ptr, *present, *node_next, tmp;

/**
 * The purpose of this method is to allocate specific blocks in memory 
 * for sizes that are specified by the user itself. The first few lines 
 * of code take care of the initialization of the list. 
 * Next, the "do-while" loop takes care of the following when malloc-ing 
 * in the order of the if-else statement block:
 * 		(1) The user requests a size bigger than what's currently there
 *		(2) Memory block is not free at the moment
 *      (3) What if there is not enough memory for the header? Then
 *			simply don't allocate space for it but return it.
 *		(4) If the above conditions are satisfied, then the user shall 
 *			obtain the memory that was requested. In this case, however,
 *			it is important to consider when the memory block is inserted
 *			in the middle of two other blocks, which was discussed in class. 
 * @param size
 *     the amount of space the user wishes to allocate
 *
 * @returns
 *     A pointer to the block of memory which has the size greater
 * 	   than or equal to the size requested by the user.
 */
 
void *mymalloc(unsigned int size, char *file, unsigned int line){
	static int INIT_FLAG = 0;
	
	if(INIT_FLAG == 0 || root->next == 0){
		root = (MyMetaData *) myblock;
		root->next = root->prev = 0;
		root->memsize = MY_SIZE - sizeof(MyMetaData);
		root->occupied = 1;
		INIT_FLAG = 1;
		//printf("size is %d\n", sizeof(MyMetaData));
		//printf("value of init_flag is %d\n", INIT_FLAG);
	}
	if(root->next != 0)
		present = root->next;
	else
		present = root;
	
	do{	
		if(present->memsize < size){
			present = present->next;	 
		}
		
		else if(!present->occupied){
			present = present->next;
		}
		
		else if(present->memsize < (size + sizeof(MyMetaData))){
			present->occupied = 0;
			//printf("Malloc was correctly invoked\n"); //for testing purposes
			return (char*)present + sizeof(MyMetaData);
		}
		
		else{
			node_next = (MyMetaData*)((char*)present + sizeof(MyMetaData));
			node_next->prev = present;
			node_next->next = present->next;
		
			if(present->next != 0){
				present->next->prev = node_next;
			}
			present->next = node_next;
			
			node_next->memsize = present->memsize - sizeof(MyMetaData) - (size*8);
			node_next->occupied = 1;
			
			present->memsize = size;
			present->occupied = 0;
			
			//printf("Malloc was correctly invoked\n"); //for testing purposes
			
			return (char*)present + sizeof(MyMetaData);
		}
	}while(!(present == 0));
		
	printf("Oops! There doesn't seem to be enough free space at the moment. Check line no. %d in file: %s\n", line, file);
	
	return 0;
}

/**
 * The purpose of this method is to join free blocks together, if there exist multiple blocks 
 * to the left or right sides of the input node pointer. Note that you cannot combine blocks
 * which exist on either side of an occupied block, i.e. ... - free - occupied - free - ...
 * EX: ... - occupied - free - free - ... becomes ... - occupied - free - ...
 * @param *n`
 *     The input node pointer which will be used as a check point
 */
	
void combinefreeblocks(MyMetaData *p){
	if(p != 0 && p->next != 0 && p->next->occupied != 0){
		p->memsize = p->memsize + p->next->memsize;
		p->next = p->next->next;
		combinefreeblocks(p->next);
	}
	
	if(p != 0 && p->prev != 0 && p->prev->occupied != 0){
		p->prev->memsize = p->prev->memsize + p->memsize;
		p->prev->next = p->next;
		combinefreeblocks(p->prev);
	}
}

/**
 * The purpose of this method is to let the OS know that you no longer need a piece
 * of dynamically allocated memory, meaning that it can be used for other purposes.
 *
 * @param *input
 *     the pointer to the allocated memory block returned by the calling malloc()
 *
 *     
 */
void myfree(void *input, char *file, unsigned int line)
{	
	//input = input + 1;
	//MyMetaData *p = (MyMetaData*)input;
	//void *in = p->memsize;
	//printf("input: %p\n", input);
	int found = 0;//indicates if the pointer was ever malloced
	if(input == 0 || input == NULL){
		printf("error\n");
		return;
	}
	MyMetaData *ptr = root;
	//printf("memsize: %d\n", 5000 - root->memsize);
	if(root != 0){
		if(input == root->prev){
			//printf("here\n");
			root->prev = 0;
			input = 0;
		}
	}
	while(ptr != 0){
	if(ptr->prev != 0 && ptr == input){
		//printf("here 2 %p %p %p %p\n", ptr->prev,ptr, ptr->next, root);
		//root->memsize = root->memsize - 8;
		ptr->prev->next = ptr->next;//setting previous node's next to the next pointer
		//printf("yes1\n");
		if(ptr->prev->next != 0)
			ptr->prev->next->prev = ptr->prev;
		//int mem = root->memsize;
		ptr->occupied = 1;
		//ptr->memsize = 1;
		//root = ptr->prev;
		//printf("here 2 %p %p\n", ptr->prev,ptr->prev->next);
		//ptr->occupied = 0;
		//ptr = 0;
		found = 1;
		//input = 0;
		//input = ptr;
	}else if(ptr == input){
		//printf("here 3\n");
		root = ptr->next;
		ptr->occupied = 0;
		input = 0;
	}
	if(ptr != 0)
		ptr = ptr->next;
	}
	if(!(found))
		printf("Pointer not found\n");
	combinefreeblocks(root);
}

