#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))
/*
Test Cases
*/


/*
Test Run 1:
Assume a 128-byte, direct-mapped cache with 8-byte cache lines (cache blocks).
*/
int test_set_1[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

/*
Test Run 2:
Assume a 64-byte, 2-way set associative cache with 8-byte cache lines (cache
blocks).
*/
int test_set_2[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

/*  
Test Run 3:
Assume a 128-byte, direct-mapped cache with 16-byte cache lines (cache blocks).
*/

/*
Test Run 4:
Assume a 64-byte, fully associative cache with 8-byte cache lines (cache
blocks).
*/
int test_set_4[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

struct block {
	int valid; //0 for invalid, 1 for valid
	int tag;
	int oldest; //1 for oldest
};

struct block cache[10000];

/*
determine if hit or miss for direct cache
*/
int isHitOrMissForDirectedMapped(int tag, int index) {
	int isHit = 0;
	//For direct-mapped, index is the cache line number.
	if (cache[index].valid && cache[index].tag == tag) {
		isHit = 1;
	}
	else {
		isHit = 0;
	}
	return isHit;	
};

/*
logic for direct cache
*/
void directCache(int cachesize, int blocksize) {
	for (int i = 0; i < sizeof(test_set_1)/sizeof(int); i++) {
		//find # of cache lines based on cache size
		int cacheLines = cachesize / blocksize; 
		
		//get current address
		unsigned int currentAddress = test_set_1[i];
		
		//find the tag, offset, and index size
		unsigned int offsetSize = log2(blocksize);
		unsigned int indexSize = log2(cacheLines);
		unsigned int tagSize = 32 - (offsetSize + indexSize);
		
		//get tag, offset, and index
		unsigned int offset = LAST(currentAddress, offsetSize);
		unsigned int tag = currentAddress >> (offsetSize + indexSize);
		int index = MID(currentAddress, (offsetSize), (32 - tagSize));

		printf("tag = %d ", tag);
		printf("index = %d ", index);
		printf("offset = %d ", offset);
		
		int answer = isHitOrMissForDirectedMapped(tag, index);
		if (answer) {
			printf("address(%d) Hit\n", currentAddress);
		}
		else {
			printf("address(%d) Miss\n", currentAddress);
			struct block newBlock;
			newBlock.tag = tag;
			newBlock.valid = 1;
			cache[index] = newBlock;
		}
	}
}

/*
determine hit or miss for fully associated cache
*/
int isHitOrMissForFully(int tag, int cacheLines) {
	int isHit = 0;
	
	for (int i = 0; i < cacheLines; i++) {
		//printf("cache block tag: %d ", cache[i].tag);
		//printf("cache block valid: %d \n", cache[i].valid);
		if (cache[i].valid && cache[i].tag == tag) {
			//printf("cache block valid: %d ", cache[i].valid);
			isHit = 1;
			return isHit;
		} else {
			isHit = 0;
		}
	}
	return isHit;	
};

/*
logic for fully associated cache
*/
void fullyCache(int cacheSize, int blockSize) {
	//find # of cache lines based on cache size
	int cacheLines = cacheSize / blockSize;
	cache[0].oldest = 1;
	
	//find the tag, offset, and index size
	unsigned int offsetSize = log2(blockSize);
	
	for (int i = 0; i < sizeof(test_set_1)/sizeof(int); i++) {
		//get current address
		unsigned int currentAddress = test_set_1[i];
		
		//get tag, offset, and index
		unsigned int offset = LAST(currentAddress, offsetSize);
		unsigned int tag = currentAddress >> (offsetSize); 
	
		printf("tag = %d ", tag);
		printf("offset = %d ", offset);

		int answer = isHitOrMissForFully(tag, cacheLines);
		
		if (answer) {
			printf("address(%d) Hit\n", currentAddress);
		}
		else {
			printf("address(%d) Miss \n", currentAddress);
			int enteredBlock = 0;
			struct block newBlock;
			newBlock.tag = tag;
			newBlock.valid = 1;
			
			for (int i = 0; i < cacheLines; i++) {
				if (!cache[i].valid) {
					cache[i] = newBlock;
					enteredBlock = 1;
					break;
				}
			}
			
			if (!enteredBlock) {
				for (int i = 0; i < cacheLines; i++) {
					if (cache[i].oldest) {
						newBlock.oldest = 0;
						cache[i] = newBlock;
						if (i != cacheLines - 1) {
							cache[i + 1].oldest = 1;
							break;
						}
						else {
							cache[0].oldest = 1;
							break;
						}
					}
				}	
			}
		}
	}
}

/*
Determine if hit or miss for set associative
*/
int isHitOrMissForSetAssoc(int k, int tag, int set) {
	int isHit = 0;
	int rowIdx = 0;
	
	//For set associative, index is the set number
	for (rowIdx = k*set; rowIdx < k*set + k; rowIdx++) {
		if (cache[rowIdx].valid && cache[rowIdx].tag == tag) {
			isHit = 1;
			break;	
		}
	}
	
	if (isHit) {
		return 1;
	}
	
	int enteredBlock = 0;
	struct block newBlock;
	newBlock.tag = tag;
	newBlock.valid = 1;
	
	//search for cache line with valid field == 0
	for (rowIdx = k*set; rowIdx < k*set + k; rowIdx++) {
		if(!cache[rowIdx].valid) {
			cache[rowIdx] = newBlock;
			enteredBlock = 1;
			break;	
		}
	}
	
	//if no valid cases check for oldest set
	if (!enteredBlock) {
		for (rowIdx = k*set; rowIdx < k*set + k; rowIdx++) {
			if (cache[rowIdx].oldest) {
				newBlock.oldest = 0;
				cache[rowIdx] = newBlock;
				if (rowIdx != ((k*set + k) - 1)) {
					cache[rowIdx + 1].oldest = 1;
					break;
				}
				else {
					cache[(k*set)].oldest = 1;
					break;
				}
			}
		}
		
	}
	return isHit;
}

void setAssocCache(int cacheSize, int blockSize, int n) {
	//find # of cache lines based on cache size
	int cacheLines = cacheSize / blockSize;
	
	//find # of sets
	int sets = cacheLines/n;
	
	//find the offset and set size
	unsigned int offsetSize = log2(blockSize);
	unsigned int setSize = cacheLines/sets;
	
	//set the oldest rows in the cache
	for (int i = 0; i < sets; i++) {
		int rowIdx = n*i; 
		cache[rowIdx].oldest = 1;
	}
		
	for (int i = 0; i < sizeof(test_set_2)/sizeof(int); i++) {
		//get current address
		unsigned int currentAddress = test_set_2[i];
		
		//get tag, offset, and index
		unsigned int offset = currentAddress % blockSize;
		unsigned int blockAddress = currentAddress / blockSize;
		unsigned int set = blockAddress % sets;
		unsigned int tag = currentAddress >> (offsetSize + setSize);
	
		printf("tag = %d ", tag);
		printf("set = %d ", set);
		printf("offset = %d ", offset);

		int answer = isHitOrMissForSetAssoc(n, tag, set);
		
		if (answer) {
			printf("address(%d) Hit\n", currentAddress);
		}
		else {
			printf("address(%d) Miss\n", currentAddress);
		}	
	}
}


/*
Takes in cachesize, number of blocks in cache, associative (n), and if 
it is a special case (direct-mapped or fully associative)

For special case, enter "direct" for direct-mapped or "fully" for
fully associative or "none" for set associative
*/
int main(int argc, char *argv[]) {
	int cachesize, blocksize, n;
	char *scase;
	
	if (argc < 5) {
		fprintf(stderr, "Need to input three arguments.\n");
	}
	
	cachesize = atoi(argv[1]);
	blocksize = atoi(argv[2]);
	n = atoi(argv[3]);
	scase = argv[4];
	
	printf("cachesize = %d\n", cachesize);
	printf("blocks in cache = %d\n", blocksize);
	printf("n-way = %d\n", n);
	printf("special case = %s\n", scase);
	
	if (strcmp(scase, "direct") == 0) {
		directCache(cachesize, blocksize);	
		return 0;	
	} else if (strcmp(scase, "fully") == 0) {
		fullyCache(cachesize, blocksize);
		return 0;	
	} else {
		setAssocCache(cachesize, blocksize, n);
		return 0;
	}
};