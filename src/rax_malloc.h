/* 基数树
 * Rax -- A radix tree implementation.
 *
 */

/* Allocator selection.
 *
 * This file is used in order to change the Rax allocator at compile time.
 * Just define the following defines to what you want to use. Also add
 * the include of your alternate allocator if needed (not needed in order
 * to use the default libc allocator). */

#ifndef RAX_ALLOC_H
#define RAX_ALLOC_H
#include "zmalloc.h"
#define rax_malloc zmalloc
#define rax_realloc zrealloc
#define rax_free zfree
#endif
