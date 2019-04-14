/* 
    File: my_allocator.cpp
*/
#include "BuddyAllocator.h"
#include <iostream>
#include <cstring>
using namespace std;

BuddyAllocator::BuddyAllocator(int _basic_block_size, int _total_memory_length) {

	//calculates number of freeLists you need and readjusts _total_memory_length
	if (_total_memory_length < _basic_block_size) {
		_total_memory_length = _basic_block_size;
	}
	else if (_basic_block_size > _total_memory_length) {
		_basic_block_size = _total_memory_length;
	}
	int numFreeLists = log2(_total_memory_length) - log2(_basic_block_size) + 1;
	//assign class member variables to input values for later use
	max_mem_size = _total_memory_length;
	min_mem_size = _basic_block_size;
	remaining_memory = _total_memory_length;

	//initializes all memory space to be used my the allocator
	TOTAL_MEMORY = new char[_total_memory_length];
	END_TOTAL_MEMORY = TOTAL_MEMORY + _total_memory_length;	//pointer to end of mem space

	//make freeLists
	freeList = vector<LinkedList*>(numFreeLists);
	int temp = _total_memory_length;
	//cout << "Making freelists..." << endl;
	for (int i = temp; i >= _basic_block_size; i = i/2) {
		LinkedList* mem = new LinkedList();
		BlockHeader* head;
		//make initial memory block contain all memory
		//all others are empty
		if (i == _total_memory_length) {
			head = reinterpret_cast<BlockHeader*>(TOTAL_MEMORY);
			head->free = true, head->next = NULL, head->size = _total_memory_length;
			mem->insert(head);
		}
		else {
			head = NULL;
			//head->free = false, head->next = NULL, head->size = i;	//size = i because i is divided by 2 each time
		}
		//add to freeList
		int vectLocation = toVectPos(i);	//converts power of 2 to inverted vector position (want largest mem space at vect(0))
		
		freeList.at(vectLocation) = mem;
	}

}

BuddyAllocator::~BuddyAllocator (){
	//FIXME: ADD REMOVAL OF ITEMS THAT ARE STILL ALLOCATED
	
	for (int i = freeList.size() - 1; i >= 0; i--) {
		//cout << "Removing freeList at " << i << endl;
		delete freeList.back();
		freeList.pop_back();
	}
	freeList.clear();
	delete(TOTAL_MEMORY);
}

char* BuddyAllocator::alloc(int _length) {
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
	//return new char [_length];	//DEFAULT

  //_MY IMPLEMENTATION_//

	//cout << "Alloc called." << endl;

	int _needed_length = _length + sizeof(BlockHeader);	//because header needs some room too
	//Check to make sure they arent asking for more memory than the max amount
	if (_needed_length > max_mem_size) {
		cerr << "Your requested memory block size was greater than the maximum size specified." << endl;
		return NULL;
	}

	//otherwise round requested length UP to closest power of 2
	int roundedLength = 0;
	//cout << "Getting rounded length" << endl;
	for (int tempMinMem = min_mem_size; tempMinMem <= max_mem_size; tempMinMem *= 2) {
		//cout << roundedLength << endl;
		if (_needed_length <= tempMinMem) {
			roundedLength = tempMinMem;
			break;
		}
		else {
			roundedLength = tempMinMem;
		}
	}
	if (roundedLength == 0) {
		//REMOVE THIS CHECK AFTER DEBUGGING
		cerr << "You should never be reading this." << endl;
		return NULL;
	}
	//check if there is enough memory left to meet this request
	if (roundedLength > remaining_memory) {
		cerr << "There is not enough remaining memory to allocate this space." << endl;
		cerr << "Requested Space: " << roundedLength << " Remaining Space: " << remaining_memory << endl;
		return NULL;
	}

	//cout << "Rounded Length is: " << roundedLength << endl;
	//cout << "Searching for availble blocks." << endl;

	//now search if there are available blocks of this size in freeList
	int listLocation = toVectPos(roundedLength);
	if (freeList.at(listLocation)->getHead() != NULL) {
		BlockHeader* currCheck = freeList.at(listLocation)->getHead();
		//we found one!
		//be sure to subtract newly allocated memory from free memory amount
		char* address = reinterpret_cast<char*>(currCheck) + sizeof(BlockHeader);	//pointer to the space AFTER the header space (ie. writable space)
		//currCheck->free = false;
		freeList.at(listLocation)->remove(currCheck);
		remaining_memory -= roundedLength;
		return address;
	}
	/*There arent any free blocks of this size yet, so allocate some (via splitting).
	We know that there IS enough memory for it from previous checks, we just have to get it.
	I made these into two seperate functions for clearity, although it could be in just one.
	Be sure to subtract newly allocated memory from free memory amount*/

	//cout << "No free blocks of size " << roundedLength << " found. Attempting to split some." << endl;

	//check the next list location. no reason to check up
	listLocation -= 1;
	for (listLocation; listLocation >= 0; listLocation--) {
		BlockHeader* currCheck = freeList.at(listLocation)->getHead();
		if (currCheck != NULL) {
			//do some splitting and return an address
			while (currCheck->size != roundedLength) {
				//currCheck->free = false;
				//cout << "Attempting to split a block the size of: " << currCheck->size << endl;
				currCheck = split(currCheck);
			}
			//cout << "Finished splitting" << endl;
			freeList.at(toVectPos(currCheck->size))->remove(currCheck);
			//freeList.at(listLocation)->remove(currCheck);
			char* address = reinterpret_cast<char*>(currCheck) + sizeof(BlockHeader);
			remaining_memory -= roundedLength;
			return address;
		}
	}
	


	//if the previous code didnt return anything then the memory space has somehow not been allocated yet
	cerr << "The total memory space has not been created yet. Please dont call alloc until after creating a Buddy Allocator." << endl;
	return NULL;

}

int BuddyAllocator::free(char* _a) {
	/* Same here! */
	//delete _a;	//DEFUALT
	
	
	//_MY IMPLEMENTATION_//
	//DONT FORGET TO SUBTRACT BLOCKHEADER LENGTH FROM ADDRESS GIVEN

	if (_a < TOTAL_MEMORY) {
		cerr << "Attempted to free a memory location which is smaller than the head of the TOTAL_MEMORY" << endl;
		return 1;
	}
	else if (_a > END_TOTAL_MEMORY) {
		cerr << "Attempted to free a memory location which is larger than END_TOTAL_MEMORY" << endl;
		return 1;
	}

	//get the real location of the address (with header)
	BlockHeader* block = reinterpret_cast<BlockHeader*>(_a - sizeof(BlockHeader));
	
	//reinsert the block into the free memory vector
	int vectPos = toVectPos(block->size);
	freeList.at(vectPos)->insert(block);
	remaining_memory += block->size;

	//recursively see if you can merge it with another block
	//dont check past vect(1) because vect(0) will never be able to merge
	for (vectPos; vectPos > 0; vectPos--) {
		BlockHeader* buddy = getbuddy(block);
		if (freeList.at(vectPos)->contains(buddy)) {
			block = merge(block, buddy);
		}
		else {
			return 0;
		}
	}
  return 0;
}

void BuddyAllocator::debug() {
	cout << "Size of BlockHeader: " << sizeof(BlockHeader) << endl;
	cout << "TOTAL_MEMORY address header: " << static_cast<void*>(TOTAL_MEMORY) << endl;
	cout << "End of TOTAL_MEMORY: " << static_cast<void*>(END_TOTAL_MEMORY) << endl;
	//cout << "FreeList head address: " << freeList.at(0)->getHead() << endl;
	cout << "Free List: " << endl;
	//output number of each member in freeList
	for (int i = 0; i < freeList.size(); ++i) {
		cout.precision(0);	//sets number of decimals to 0. make sure to set this back if needed
		cout << fixed <<  pow(2, log2(max_mem_size) - i) << ": ";	//fixed must also be changed back if we want sci notation
		cout << freeList.at(i)->getCount() << endl;
	}

}

