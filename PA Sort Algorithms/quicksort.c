#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quicksort.h"
#define SWAP(x, y) do{uint32_t temp = x; x = y; y = temp; }while(0)

void quickSort(uint32_t a[], uint32_t start, uint32_t length, uint32_t *moves, uint32_t *compares)
{
	uint32_t p;
	if(start < length)
	{
		// Recursively call quickSort to sort both sides of the array
		p = partition(a, start, length, moves, compares);
		quickSort(a, start, (p-1), moves, compares);
		quickSort(a, (p+1), length, moves, compares);
	}
	return;
}

uint32_t partition(uint32_t a[], uint32_t start, uint32_t end, uint32_t *moves, uint32_t *compares)
{
	// Set pivot as the first element, along with i for the wall
        uint32_t pivot = start, i = start;
        while (1)
        {
		// Increment i if current element on the left side is less than pivot element and index i is less than the end index
                while ((a[i] <= a[pivot]) && (i < end))
		{
			(*compares)++;                
                        i++;
                }
		// Decrement end index if elements to the right of the pivot are smaller
                while (a[end] > a[pivot])
                {
			(*compares)++;
                        end--;
                }
		// Move the current element to the end of the array if the index of end is greater than the index of i
                if (end > i)
                {
			(*compares)++;
                        (*moves) += 3;
                        SWAP(a[i], a[end]);
                }
                else
                {
                        break;
                }
        }
	(*moves) += 3;
        SWAP(a[pivot], a[end]);
        return (end);
}
