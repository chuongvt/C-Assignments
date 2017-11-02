/*
 * minsort.c
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "minsort.h"
#define SWAP(x, y) do{uint32_t temp = x; x = y; y = temp; }while(0)

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last, uint32_t *compares)
{
	// We first assume that the first number will be the smallest
        uint32_t smallest = first;
	// Loops through the array and finds the smallest array index and returns it
        for (uint32_t i = first; i < last; i = i + 1)
        {
		smallest = a[i] < a[smallest] ? i : smallest;
		(*compares)++;
        }
        return smallest;
}

void minSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	// Loops through array and sort by according to the smallest elements
        for (uint32_t i=0; i<length-1; i = i + 1)
        {
                uint32_t smallest = minIndex(a, i, length, compares);
		// Don't swap with yourself 
                if (smallest != i)
                {
                        SWAP(a[smallest], a[i]);
			(*moves) += 3;
                }
        }
        return;
}
