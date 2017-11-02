#include <stdio.h>
#include <stdlib.h>
#include "insertionsort.h"

void insertionSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	// Loop through array
	for (uint32_t i = 1; i < length; i++)
	{
		(*moves)++;
		uint32_t currentNum = a[i];
		int j = i - 1;
		// Inserts item into correct position
		while (j >= 0 && a[j] > currentNum)
		{
			(*compares)++;
			(*moves)++;
			a[j+1] = a[j];
			j = j - 1;
		}
		a[j+1] = currentNum;
	}
}
