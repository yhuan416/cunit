/*
 * Allocate small amounts of memory from a static pool, This memory can be leaked without issue.
 */
#include "CUnit/InternalPoolMalloc.h"
#include <errno.h>
#include <assert.h>

#define MAX_INTERNAL_BLOCKS 64   // how many blocks we can give out in total
#define BLOCK_SIZE           256  // the size of each block

struct internal_block {
    char allocated;
    char m[BLOCK_SIZE];
};

static struct internal_block blocks[MAX_INTERNAL_BLOCKS];


void * Internal_CU_StaticMalloc(size_t sz)
{
    int i;
    assert (sz <= BLOCK_SIZE);
    for (i = 0; i < MAX_INTERNAL_BLOCKS; i++) {
        if (!blocks[i].allocated) {
            blocks[i].allocated = 1;
            return &blocks[i].m;
        }
    }
    errno = ENOMEM;
    return NULL;
}

void Internal_CU_StaticFree(void *p){
    int i;
    for (i = 0; i < MAX_INTERNAL_BLOCKS; i++) {
        if (p == (void*)(&(blocks[i].m))) {
            blocks[i].allocated = 0;
            break;
        }
    }
}