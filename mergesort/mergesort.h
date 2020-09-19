#ifndef MERGESORT_H_GUARD
#define MERGESORT_H_GUARD

#include <stdbool.h>

#define UNIT_TESTING

void mergesort(int size, int values[]);
void mergesort_range(int *values, int start_index, int end_index);
void merge_ranges(int *values, int start_index, int mid_point, int end_index);
bool needs_sorting(int range_size);

#endif
