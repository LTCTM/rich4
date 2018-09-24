/*
 * Copyright (C)  2018 Iru Cai <mytbk920423@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdlib.h>
#include <string.h>
#include "data_struct.h"

static inline void mem_copy_words(void *dst, void *src, size_t n)
{
	memcpy(dst, src, n*2);
}

struct st * allocate_some_struct(int a1, int a2, int a3, int a4)
{
	struct st * newst = (struct st *)malloc(a1 * a2 * 2 + 12);
	newst->f0 = a1;
	newst->f2 = a2;
	newst->f4 = a3;
	newst->f6 = a4;
	newst->f8 = newst->data;
}

/* this function looks buggy and can crash the game */

struct st * fcn_00451a97(struct st *a1, struct st *a2, int a3, int a4, int a5, int a6)
{
	if (a2 == NULL) {
		a2 = malloc(a5 * a6 * 2 + 12);
	}
	
	a2->f0 = a5; /* number of words(16b) per block? */
	a2->f2 = a6; /* number of blocks? */
	a2->f4 = a2->f6 = 0;
	a2->f8 = a2->data;

	int16_t *ebx = &a1->f8[a1->f0 * a4 + a3];
	int16_t *esi = a2->f8;

	for (int i = 0; i < a6; i++) {
		mem_copy_words(esi, ebx, a5); /* copy a5 words(16b) from ebx to esi */
		esi = &esi[a5];
		ebx = &ebx[a1->f0];
	}
	return a2;
}
