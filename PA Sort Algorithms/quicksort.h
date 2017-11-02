#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stdint.h>

void quickSort(uint32_t *, uint32_t, uint32_t, uint32_t *, uint32_t *);
uint32_t partition(uint32_t *, uint32_t, uint32_t, uint32_t *, uint32_t *);

#endif
