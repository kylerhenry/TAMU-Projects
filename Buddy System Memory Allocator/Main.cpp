#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <unistd.h>

int main(int argc, char ** argv) {

	int opt;
	int basic_block_size = 128, memory_length = 128 * 1024 * 1024;
	while ((opt = getopt(argc, argv, "b:s:")) != -1) {
		switch (opt) {
		case 'b':
			basic_block_size = atoi(optarg);
			break;
		case 's':
			memory_length = atoi(optarg);
			break;
		case '?':
			if (optopt == 'b' || optopt == 's') {
				fprintf(stderr, "Option %c needs an argument\n", optopt);
			}
			else {
				fprintf(stderr, "Unknown option %c. \n", optopt);
			}
			break;
		default:
			basic_block_size = 128, memory_length = 128 * 1024 * 1024;
		}
	}
	//make sure inputs are valid
	if (basic_block_size > memory_length) {
		cerr << "Basic block size " << basic_block_size << " is greater than the max memory " << memory_length << ". Changing the basic block size to match max memory size." << endl;
		basic_block_size = memory_length;
	}
	//make sure inputs are non-zero
	if (basic_block_size == 0 || memory_length == 0) {
		cerr << "One of your inputs was a zero." << endl;
		return 1;
	}
	//check if inputs are a power of two
	if (basic_block_size & basic_block_size - 1) {
		cerr << "Basic block size was not a power of 2." << endl;
		return 1;
	}
	if (memory_length & memory_length - 1) {
		cerr << "Memory length was not a power of 2." << endl;
		return 1;
	}


	// create memory manager
	BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);

	// test memory manager
	Ackerman* am = new Ackerman ();
	am->test(allocator); // this is the full-fledged test. 

	//////////////////////////////////////////////////////////CUSTOM DEBUG//////////////////////////////////////////////
	//char* loc = allocator->alloc(memory_length/ 16);
	//void* locaddr = static_cast<void*>(loc);
	//BlockHeader* block_with_header = reinterpret_cast<BlockHeader*>(loc - sizeof(BlockHeader));
	//cout << "Location Allocated (after block header): " << locaddr << endl;
	//cout << "Location of BlockHeader (should be the start memory address): " << block_with_header << endl;
	//cout << "Size of block allocated: " << block_with_header->size << endl;

	//char* loc2 = allocator->alloc(memory_length / 16);
	//void* locaddr2 = static_cast<void*>(loc2);
	//BlockHeader* block_with_header2 = reinterpret_cast<BlockHeader*>(loc2 - sizeof(BlockHeader));
	//cout << "Location Allocated (after block header): " << locaddr2 << endl;
	//cout << "Location of BlockHeader (should be the start memory address): " << block_with_header2 << endl;
	//cout << "Size of block allocated: " << block_with_header2->size << endl;
	//cout << "Difference in alloc positions: " << (char*)locaddr2 - (char*)locaddr << endl;
	////cout << "Free?: " << block_with_header->free << endl;
	////cout << "Next free?: " << block_with_header->next->free << endl;

	//cout << "ALLOC DEBUG: " << endl;
	//allocator->debug();

	//cout << "+++FREEING BLOCK 1+++: " << endl;
	//cout << "Freed successfully?: " << !allocator->free(loc) << endl;
	//cout << "FREE1 DEBUG: " << endl;
	//allocator->debug();

	//cout << "+++FREEING BLOCK 2+++: " << endl;
	//cout << "Freed successfully?: " << !allocator->free(loc2) << endl;
	//cout << "FREE2 DEBUG: " << endl;
	//allocator->debug();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// destroy memory manager
	delete allocator;
	return 0;
}
