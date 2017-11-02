#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

struct bitV *newVec(uint32_t l) // Creates a new bit vector
{
	bitV *aVec = (bitV *) malloc(sizeof(bitV));
	aVec -> vector = (uint8_t *) calloc(l/8+1, sizeof(uint8_t));
	aVec -> length = l;
    	return aVec;
}

void delVec(bitV *bv) // Deletes a vector
{
	free(bv->vector);
	free(bv);
	return;
}

void oneVec(bitV *bv) // Sets an entire vector to all 1s
{
	for (uint32_t i=0; i < (bv -> length); i++)
	{
		bv -> vector[i >> 3] |= (0x1 << (i%8));
	}
	return;	
}

void setBit(bitV *bv, uint32_t m) // Sets a specified bit to 1
{
	bv -> vector[m >> 3] |= (0x1 << (m%8));
	return;	
}

void clrBit(bitV *bv, uint32_t m) // Sets a specified bit to 0
{
	bv -> vector[m >> 3] &= ~(0x1 << (m%8));
	return;
}

uint8_t valBit(bitV *bv, uint32_t m) // Returns the value of a bit
{
	return (bv -> vector[m >> 3] & (0x1 << (m%8))) >> (m%8);	
}

uint32_t lenVec(bitV *bv) // Returns the length of a vector
{
	return bv -> length;
}
