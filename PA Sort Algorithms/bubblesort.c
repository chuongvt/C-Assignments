#include <stdio.h>
#include <stdlib.h>
#include "bubblesort.h"
#define SWAP(x, y) do{uint32_t temp = x; x = y; y = temp; }while(0)

void bubbleSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	// Flag to check for swaps
	int flag;
	uint32_t arrayLen = length;
	for (uint32_t i = arrayLen-1; i > 0; i = i - 1)
	{
		flag = 0;
		for (uint32_t j = 1; j <= i; j = j + 1)
		{
			// Check if right of adjacent pair is greater. If so, then swap
			if (a[j-1] > a[j])
			{
                		(*compares)++;
				SWAP(a[j-1], a[j]);
				(*moves) += 3;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}
