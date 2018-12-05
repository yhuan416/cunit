/*
 * Primitive memory allocation based on static blocks
 *
 * Intended for internal CUnit use only
 *
 */

#ifndef CU_INTERNALPOOLMALLOC_H
#define CU_INTERNALPOOLMALLOC_H

#include "stdio.h"

/**
 * Allocate a block of memory
 * @param sz
 * @return
 */
void* Internal_CU_StaticMalloc(size_t sz);

/**
 * Free a pointer allocated by Internal_CU_StaticMalloc()
 * @param p
 */
void Internal_CU_StaticFree(void *p);


#endif //CU_INTERNALPOOLMALLOC_H
