/* 
    File: my_allocator.h

    Original Author: R.Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/08

    Modified:

 */

#ifndef _BuddyAllocator_h_                   // include file only once
#define _BuddyAllocator_h_
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
typedef unsigned int uint;

/* declare types as you need */

class BlockHeader{
	// decide what goes here
	// hint: obviously block size will go here
public:
	uint size;	//size of block
	bool free;	//indicates is the block is free in memory or not
	BlockHeader* next;	//pointer to the next block size of memory (down the list)
};

class LinkedList{
	// this is a special linked list that is made out of BlockHeader s. 
private:
	BlockHeader* head = NULL;		// you need a head of the list
	int count = 0;
public:
	void insert(BlockHeader* b) {	// adds a block to the list
									//assumes that there already exists a head to the list
		if (head == NULL) {
			head = b;
		}
		else {
			BlockHeader* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = b;
			b->next = NULL;
		}
		count++;
	}

	void remove(BlockHeader* b) {  // removes a block from the list
		BlockHeader* temp = head;
		if (temp == b) {
			//b is the head
			temp = head->next;
			head->next = NULL;
			head = temp;
		}
		else {
			while (temp->next != b) {
				temp = temp->next;
			}
			if (b->next == NULL) {	//if b is last item in list
				temp->next = NULL;
			}
			else {					//if b is intermediary or head
				temp->next = b->next;
				b->next = NULL;
			}
		}
		count--;
	}

	//checks if the LL has a certain block in it (ie. the block is free)
	bool contains(BlockHeader* block) {
		BlockHeader* temp = head;
		while (temp != NULL) {
			if (temp == block) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	//count accessor
	int getCount() {
		return count;
	}

	//head accessor
	BlockHeader* getHead() {
		return this->head;
	}
};


class BuddyAllocator {
private:
	/* declare member variables as necessary */

	//start of all memory space available to buddy allocator
	char* TOTAL_MEMORY;

	vector<LinkedList*> freeList;
	char* END_TOTAL_MEMORY;
	int max_mem_size;
	int min_mem_size;
	int remaining_memory;

private:
	/* private function you are required to implement
	 this will allow you and us to do unit test */

	 // given a block address, this function returns the address of its buddy 
	BlockHeader* getbuddy(BlockHeader * addr) {
		char* buddy = ((char*)addr - (char*)TOTAL_MEMORY ^ (addr->size)) + (char*)TOTAL_MEMORY;
		BlockHeader* bud = (BlockHeader*)buddy;
		return bud;
	}

	// checks whether the two blocks are buddies or not
	bool arebuddies(BlockHeader* block1, BlockHeader* block2) {
		BlockHeader* block1Buddy = getbuddy(block1);
		if (block1Buddy == block2) {
			return true;
		}
		return false;
	}

	// this function merges the two blocks returns the beginning address of the merged block
	// note that either block1 can be to the left of block2, or the other way around
	BlockHeader* merge(BlockHeader* block1, BlockHeader* block2) {
		//ensure the two blocks can actaully be merged according to rules
		if (block1->size != block2->size) {
			cerr << "Attempted to merge blocks of different sizes." << endl << "Block1 size: " << block1->size << endl << "Block2 size: " << block2->size << endl;
			return NULL;
		}
		if (!arebuddies(block1, block2)) {
			cerr << "Attempted to merge blocks which are not buddies." << endl;
			return NULL;
		}
		if (!block1->free || !block2->free) {
			cerr << "Attempted to merge blocks, one of which is not free." << endl;
			return NULL;
		}

		//merge the blocks
		freeList.at(toVectPos(block1->size))->remove(block1);	//remove the blocks from their current list
		freeList.at(toVectPos(block2->size))->remove(block2);	//remove the block from its current list
		//assign the new information to the earliest addressed BlockHeader to ensure the memory stays contiguous
		if ((char*)block1 < (char*)block2) {
			//delete(block2);
			block1->size *= 2;
			freeList.at(toVectPos(block1->size))->insert(block1);
			return block1;
		}
		else {
			//delete(block1);
			block2->size *= 2;
			freeList.at(toVectPos(block2->size))->insert(block2);
			return block2;
		}
		

	}
	
	BlockHeader* split(BlockHeader* block){
		// splits the given block by putting a new header halfway through the block
		// also, the original header needs to be corrected
		//cout << "Split Called." << endl;
		if (block->size <= min_mem_size) {
			cerr << "Cannot split block of size " << block->size << " because it is already the smallest it can be." << endl;
			return NULL;
		}

		//assign new block size
		block->size /= 2;
		//make the new block
		BlockHeader* newBlock = reinterpret_cast<BlockHeader*>((char*)block + block->size);
		newBlock->free = true, newBlock->size = block->size;
		BlockHeader* tempBlock = block;

		//remove the block from its current list
		freeList.at(toVectPos(block->size * 2))->remove(block);

		//insert the blocks to their new locations
		freeList.at(toVectPos(tempBlock->size))->insert(tempBlock);
		freeList.at(toVectPos(newBlock->size))->insert(newBlock);

		return tempBlock;
	}


public:
	BuddyAllocator (int _basic_block_size, int _total_memory_length); 
	/* This initializes the memory allocator and makes a portion of 
	   ’_total_memory_length’ bytes available. The allocator uses a ’_basic_block_size’ as 
	   its minimal unit of allocation. The function returns the amount of 
	   memory made available to the allocator. If an error occurred, 
	   it returns 0. 
	*/ 

	~BuddyAllocator(); 
	/* Destructor that returns any allocated memory back to the operating system. 
	   There should not be any memory leakage (i.e., memory staying allocated).
	*/ 

	char* alloc(int _length); 
	/* Allocate _length number of bytes of free memory and returns the 
		address of the allocated portion. Returns 0 when out of memory. */ 

	int free(char* _a); 
	/* Frees the section of physical memory previously allocated 
	   using ’my_malloc’. Returns 0 if everything ok. */ 
   
	void debug ();
	/* Mainly used for debugging purposes and running short test cases */
	/* This function should print how many free blocks of each size belong to the allocator
	at that point. The output format should be the following (assuming basic block size = 128 bytes):

	128: 5
	256: 0
	512: 3
	1024: 0
	....
	....
	 which means that at point, the allocator has 5 128 byte blocks, 3 512 byte blocks and so on.*/

	//use this to convert raw data sizes to their position in the vector field
	int toVectPos(int powerOfTwo) {
		return log2(max_mem_size) - log2(powerOfTwo);
	}
};

#endif 
