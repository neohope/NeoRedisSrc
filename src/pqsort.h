/* 
 * 部分快速排序
 *
 * The following is the NetBSD libc qsort implementation modified in order to
 * support partial sorting of ranges for Redis.
 *
 * Copyright(C) 2009-2012 Salvatore Sanfilippo. All rights reserved.
 *
 * The original copyright notice follows. */

/*	$NetBSD: qsort.c,v 1.19 2009/01/30 23:38:44 lukem Exp $	*/

#ifndef __PQSORT_H
#define __PQSORT_H

void
pqsort(void *a, size_t n, size_t es,
    int (*cmp) (const void *, const void *), size_t lrange, size_t rrange);

#endif
