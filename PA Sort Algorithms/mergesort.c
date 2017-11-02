#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

void mergeLists(uint32_t left[], uint32_t right[], uint32_t array[], uint32_t *moves, uint32_t *compares, uint32_t leftSize, uint32_t rightSize)
{	
	// Indices for left, right, and main arrays
	uint32_t l = 0, r = 0, i = 0;
        while (1)
        {
		// Both lists hold elements
                if (l < leftSize && r < rightSize)
                {
			// Left is smaller
                        if (left[l] < right[r])
                        {
				(*compares)++;
				(*moves) += 2;
				array[i] = left[l];
				i++;
				l++;
                        }
			// Right is smaller
			else
			{	
				(*compares)++;
				(*moves) += 2;
				array[i] = right[r];
				i++;
				r++;
			}
			
                }
		// Left array only contains elements
		else if (l < leftSize)
		{
			(*moves) += 2;
			array[i] = left[l];
			i++;
			l++;
		}
		// Right array only contains elements
		else if(r < rightSize)
		{
			(*moves) += 2;
			array[i] = right[r];
			i++;
			r++;
		}
		// Breaks when sorting is done
		else
		{
			break;
		}
	}
	return;
}

Void mergeSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	uint32_t i, middle;
	uint32_t *leftList, *rightList;
	if (length > 1)
	{
		// Set length of middle of aray
		middle = length/2; 
		// Array for left half
		leftList = (uint32_t *) calloc(middle, sizeof(uint32_t));	
		//Array for right half
		rightList = (uint32_t *) calloc((length-middle), sizeof(uint32_t)); 
		// Add elements of array to left half
		for (i = 0; i < middle; i++)	
		{
			leftList[i] = a[i];
		}
		// Add elements of array to right half
		for(i = middle; i < length; i++) 
		{
			rightList[(i-middle)] = a[i];
		}
		// Sort the left half and right half, then merge the lists together
		mergeSort(leftList, middle, moves, compares);	
		mergeSort(rightList, (length-middle), moves, compares);
		mergeLists(leftList, rightList, a, moves, compares, middle, (length-middle));
		free(leftList);
		free(rightList);
	}
	return;
}


