#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <unistd.h>
#define MASK 0x00ffffff
#include "minsort.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"

void printStuff(uint32_t *array, uint32_t moves, uint32_t arrayAmount, uint32_t compares, uint32_t printNElements);
void makeArray(uint32_t randomSeed, uint32_t arraySize, uint32_t *array);

int main(int argc, char *argv[])
{
	uint32_t Aopt = 0, mopt = 0, bopt = 0, iopt = 0, qopt = 0, Mopt = 0;
	int c;
	uint32_t printNElements = 100; // Default print up to N elements is 100
	uint32_t randomSeed = 8062022; // Default random seed is 8222022
	uint32_t arraySize = 100;      // Default array size is 100
        uint32_t moves, compares;      // Counter variables, move and compare, for each sort
        uint32_t *pMoves = &moves;     // Pointer variables for move and compare
        uint32_t *pCompares = &compares;
	opterr = 0;
	
	// Getopt implementation for parsing the command line arguments
	while ((c = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
	{
		switch (c)	
		{
                        case 'p':
				printNElements = atoi(optarg);
				break;
                        case 'r':
				randomSeed = atoi(optarg);
				break;
                        case 'n':
				arraySize = atoi(optarg);
				break;
			case 'A':
				Aopt = 1;
				break;
			case 'm':
				mopt = 1;
				break;
			case 'b':
				bopt = 1;
				break;
			case 'i':
				iopt = 1;
				break;
			case 'q':
				qopt = 1;
				break;
			case 'M':
				Mopt = 1;
				break;	
			case '?':
				break;
		}

	}
	// Option for all sorts
	if(Aopt == 1)
	{
		// Sets all sorts to 1
		mopt = 1;
		bopt = 1;
		iopt = 1;
		qopt = 1;
		Mopt = 1;			
	}
	// Option for minsort
	if(mopt == 1)
	{
		uint32_t *array = (uint32_t *) calloc(arraySize, sizeof(uint32_t));
		moves = 0;
		compares = 0;
		printf("Min Sort\n");
		makeArray(randomSeed, arraySize, array);
		minSort(array, arraySize, pMoves, pCompares);
		printStuff(array, moves, arraySize, compares, printNElements);
		free(array);
	}
	// Option for bubblesort
	if(bopt == 1)
	{
		uint32_t *array = (uint32_t *) calloc(arraySize, sizeof(uint32_t));
		moves = 0;
		compares = 0;
		printf("Bubble Sort\n");
                makeArray(randomSeed, arraySize, array);
                bubbleSort(array, arraySize, pMoves, pCompares);
                printStuff(array, moves, arraySize, compares, printNElements);
                free(array);
		
	}
	// Option for insertionsort
	if(iopt == 1)
	{
                uint32_t *array = (uint32_t *) calloc(arraySize, sizeof(uint32_t));
                moves = 0;
                compares = 0;
                printf("Insertion Sort\n");
                makeArray(randomSeed, arraySize, array);
                insertionSort(array, arraySize, pMoves, pCompares);
                printStuff(array, moves, arraySize, compares, printNElements);
                free(array);		
	}
	// Option for quicksort
	if(qopt == 1)
	{
		int start=0;
                uint32_t *array = (uint32_t *) calloc(arraySize+1, sizeof(uint32_t));
                moves = 0;
                compares = 0;
                printf("Quick Sort\n");
                makeArray(randomSeed, arraySize, array);
                quickSort(array, start, (arraySize-1), pMoves, pCompares);
                printStuff(array, moves, arraySize, compares, printNElements);
                free(array);	
	}
	// Option for mergesort
	if(Mopt == 1)
	{
                uint32_t *array = (uint32_t *) calloc(arraySize+1, sizeof(uint32_t));
                moves = 0;
                compares = 0;
                printf("Merge Sort\n");
                makeArray(randomSeed, arraySize, array);
                mergeSort(array, arraySize, pMoves, pCompares);
                printStuff(array, moves, arraySize, compares, printNElements);
                free(array);
	}
	return 0;
}

// Function to make an array for each sort
void makeArray(uint32_t randomSeed, uint32_t arraySize, uint32_t *array)
{
	uint32_t i = 1; 
	srand(randomSeed);
        for(i = 0; i < arraySize; i++)
	{
                array[i] = (rand() & MASK);
        }
	return;
}

// Function to print information about each sort
void printStuff(uint32_t *array, uint32_t moves, uint32_t arrayAmount, uint32_t compares, uint32_t printNElements){
        uint32_t i = 0;
	uint32_t spacing = 0;
	printf("%d elements\n", arrayAmount);
        printf("%d moves\n", moves);
        printf("%d compares\n", compares);
        for(i = 0; i < printNElements; i++)
        {
		if(spacing < 7)
		{	
                	printf("%10d", array[i]);
			spacing++;
		}
		if (spacing == 7){
			printf("\n");
			spacing = 0;
		}
        }
	printf("\n");
	return;
}
