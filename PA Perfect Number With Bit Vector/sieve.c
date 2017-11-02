/*
 * sieve.c
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

#include <stdio.h>
#include <math.h>
#include "sieve.h"
#include "bv.h"

// Sieve a vector to find all primes
void sieve(bitV *v) 
{
	oneVec(v); 	// First assumes that all are prime
	clrBit(v, 0);	// 0 is 0
	clrBit(v, 1);	// 1 is unity
	setBit(v, 2);	// 2 is prime
	for (uint32_t i = 2; i <= sqrtl(lenVec(v)); i++) 
	{
		if (valBit(v, i))	// If it's prime
		{
			for (uint32_t k = 0; (k + i) * i <= lenVec(v); k++)
			{
				clrBit(v, (k + i) * i);	// It's multiples are composite
			}
		}
	}
	return;
}
			
