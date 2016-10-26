int test_set_1[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

int test_set_2[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

int test_set_3[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

int test_set_4[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

// valid is an int that states validitiy of the bit (0 = invalid, 1 = valid)
// tag being held
// pointer to next line in the cache
struct block {
	int valid;
	int tag;
	struct block *next;
}
  
struct cache {
	int hits;
	int misses;
	int reads;
	int writes;
	int cache_size;
	int block_size;
	int numLines;
	int writePolicy;
	cacheLine* cacheLines;
}

/* getBinary
 *
 * Converts an unsigned integer into a string containing it's
 * 32 bit long binary representation.
 *
 *
 * @param   num         number to be converted
 *
 * @result  char*       binary string
 */
char *convertToBinary(unsigned int num) {
	char* bstring;
	int i;
	
	bstring = (char*) malloc(sizeof(char) * 33);
	assert(bstring != NULL);
	
	brstring[32] = '\0';
	
	for (i = 0; i < 32: i++) {
		bstring[32 - 1 - i] = (num == ((1 << i) | num)) ? '1' : '0';
	}
	
	return bstring;
}

/* formatBinary
 *
 * Converts a 32 bit long binary string to a formatted version
 * for easier parsing. The format is determined by the TAG, INDEX,
 * and OFFSET variables.
 *
 * Ex. Format:
 *  -----------------------------------------------------
 * | Tag: 18 bits | Index: 12 bits | Byte Select: 4 bits |
 *  -----------------------------------------------------
 *
 * Ex. Result:
 * 000000000010001110 101111011111 00
 *
 * @param   bstring     binary string to be converted
 *
 * @result  char*       formated binary string
 */

char *formatBinary(char *bstring)
{
    char *formatted;
    int i;
    
    /* Format for Output */
    
    formatted = (char *) malloc(sizeof(char) * 35);
    assert(formatted != NULL);
    
    formatted[34] = '\0';
    
    for(i = 0; i < TAG; i++)
    {
        formatted[i] = bstring[i];
    }
    
    formatted[TAG] = ' ';
    
    for(i = TAG + 1; i < INDEX + TAG + 1; i++)
    {
        formatted[i] = bstring[i - 1];
    }
    
    formatted[INDEX + TAG + 1] = ' ';
    
    for(i = INDEX + TAG + 2; i < OFFSET + INDEX + TAG + 2; i++)
    {
        formatted[i] = bstring[i - 2];
    }

    return formatted;
}

struct cacheLine cache[10000];

  struct row { int valid; int tag; struct row *prev };
  struct row *firstRow = NULL;
  struct row cache[5000];
  int maxCacheIndex;
  


//N-way Set associative
numberOfBlocks = cacheSize (Bytes) / blockSize (Bytes)
numberOfSets = numberOfBlocks / N
offsetWidth = log2(blockSize)
indexWidth = log2(numberOfSets)
tagWidth = 32 - offsetWidth - indexWidth

struct block {
	
}
  
int main() {
	
	for () {
		// get next address
	}
	
	tag = 0;
	index = 0;
	
	//we declare isHitOrMissForDirectMapped above. But we define it below.
	
	answer = isHitOrMissForDirectMapped(tag, index);
	if (answer) {
		printf("address(%d) Hit\n", address);
	}
	else {
		printf("address(%d) Miss\n", address);
	}
	return 0; // the fnc main returns 0 for success. anything else is error number
}

int isHitOrMissForDirectedMapped(int tag, int index) {
	int rowIdx = 0;
	//For direct-mapped, index is the cache line number.
	if (cache[index].valid && cache[index].tag == tag) {
		isHit = true;
	}
	else {
		isHit = false;
	}
	return isHit;
}
int isHitOrMissForSetAssoc(int k, int tag, int index) {
	int isHit = 0; //Initialize isHit to default: false
	int rowIdx = 0;
	
	//For set associative, index is the set number
	for (rowIdx = k*index; rowIdx < k*index + k; rowIdx++) {
		if (cache[rowIdx].valid && cache[rowIdx].tag == tag) {
			isHit = true;
			break;
		}
	}
	//Now, isHit has value true if we found a hit
	if (isHit) {
		return 1; //return true
	}
	
	//Else search for cache line with valid field == 0 (false)
	for (rowIdx == k*index; rowIdx < k*index + k; rowIdx++) {
		if (cache[rowIdx].valid == 0) {
			break;
		}
	}
	
	//If we didn't find a cache line with valid field false, then evict cache line
	if (rowIdx >= k*index + k) {
		//if failed to find invalid cache line
	}
	
	return isHit;
}

//Initialize all valid fields to 0 (false)

//One free and one used linked list for each set
struct freeList[numSets];
struct usedList[numSets];

//Initialize usedList[] and freeList[]
for (set = 0; set < numSets; set++) {
	usedList[set] = NULL;
	freeList[set] =& cache[set * LinesPerSet];
}
for (set = 0; set < numSets; set++) {
	for (index = set*linesPerSet; index < (set+1)*linesPerSet; index++) {
		cache[index].next = & cache[index+1];
	}
	cache[(set+1)*linesPerSet - 1].next = NULL;
}

struct cacheLine * getFreeCacheLine(int set) {
	if (freeList[set] == NULL) {
		evictCacheLine(int set);
		//Now we know the freeList[set] [points to a real cache line]
	}
	struct cacheLine * tmp = freeList[set];
	freeList[set] = tmp->next; // Now freeList[set] is correct
	tmp->next = usedList[set];
	usedList[set] = tmp; //Now usedList[set] is correct
	return usedList[set];
}

int main(char argc, char **argv)
{
    /* Local Variables */
    int write_policy, counter, i, j;
    Cache cache;
    char mode, address[100];
	
	cache = createCache(CACHE_SIZE, BLOCK_SIZE, write_policy);
	
	counter = 0;
	
	while (/*read input line*/ != NULL) {
		
	}
    
    /* Technically a line shouldn't be longer than 25 characters, but
       allocate extra space in the buffer just in case */
    char buffer[LINELENGTH];

    
    /* Write Policy */
    if(strcmp(argv[1], "wt") == 0)
    {
        write_policy = 0;
        if(DEBUG) printf("Write Policy: Write Through\n");
    }
    else if(strcmp(argv[1], "wb") == 0)
    {
        write_policy = 1;
        if(DEBUG) printf("Write Policy: Write Back\n");
    }
    else
    {
        fprintf(stderr, "Invalid Write Policy.\nUsage: ./sim [-h] <write policy> <trace file>\n");
        return 0;
    }
    
    /* Open the file for reading. */
    file = fopen( argv[2], "r" );
    if( file == NULL )
    {
        fprintf(stderr, "Error: Could not open file.\n");
        return 0; 
    }

    cache = createCache(CACHE_SIZE, BLOCK_SIZE, write_policy);
    
    counter = 0;
    
    while( fgets(buffer, LINELENGTH, file) != NULL )
    {
        if(buffer[0] != '#')
        {
            i = 0;
            while(buffer[i] != ' ')
            {
                i++;
            }
            
            mode = buffer[i+1];
            
            i = i+2;
            j = 0;
            
            while(buffer[i] != '\0')
            {
                address[j] = buffer[i];
                i++;
                j++;
            }
            
            address[j-1] = '\0';
            
            if(DEBUG) printf("%i: %c %s\n", counter, mode, address);
            
            if(mode == 'R')
            {
                readFromCache(cache, address);
            }
            else if(mode == 'W')
            {
                writeToCache(cache, address);
            }
            else
            {
                printf("%i: ERROR!!!!\n", counter);
                fclose(file);
                destroyCache(cache);
                cache = NULL;
                
                return 0;
            }
            counter++;
        }
    }
    
    if(DEBUG) printf("Num Lines: %i\n", counter);
    
    printf("CACHE HITS: %i\nCACHE MISSES: %i\nMEMORY READS: %i\nMEMORY WRITES: %i\n", cache->hits, cache->misses, cache->reads, cache->writes);
    
    /* Close the file, destroy the cache. */
    
    fclose(file);
    destroyCache(cache);
    cache = NULL;
    
    return 1;
}

Cache createCache(char size, char blocks) {
	
	
}