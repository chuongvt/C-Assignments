#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

// This function checks whether if a number is perfect or not. If it's perfect, then show all divisors with the number
void isPerfect(uint32_t n)
{
        uint32_t divisors[32];
        uint32_t sum=0, count = 0, num = n;
        for (uint32_t i=1; i < num; i++)
        {
                if (num%i == 0)
                {
                        divisors[count] = i;
                        sum += i;
                        count++;
                }
        }
        if (sum == num) // If the sum of divisors adds up to the number
        {
                printf("%u E: ", num);
                for (uint32_t j=0; j<count; j++)
                {
                        printf("%u ", divisors[j]);
                }
                printf("\n");
        }
	return;
}

// This function gives the prime factorization of composite numbers
void factor(uint32_t *p, uint32_t n, uint32_t c)
{	
	uint32_t num = n;
	printf("%u C: ", num);
	for (uint32_t i=0; i<c; i++)
	{
		while ((num != 1) && (num%p[i]==0))
		{
			num /= p[i];
			printf("%u ", p[i]);
		}
	}
	printf("\n");
	return;
}

int main()
{
        uint32_t n = 100000, count = 0;
        bitV *v = newVec(n);
        sieve(v);
	uint32_t factors[v -> length];

        for (uint32_t i=2; i<=(v->length); i++)
        {
		// If prime, print out prime
                if (valBit(v, i))
                {
                        printf("%u P\n", i);
			factors[count] = i;
			count++;
                }
                else
                {
                	factor(factors, i, count); // Else, print out prime factors of the composite
			isPerfect(i); // If it's a perfect number, identify it and print divisors
                }
        }	
	delVec(v); // Delete the vec
        return 0;
}
