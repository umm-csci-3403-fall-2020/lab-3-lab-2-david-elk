#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "mergesort.h"

void mergesort(int size, int *values) {
  mergesort_range(values, 0, size);
  return;
}

void mergesort_range(int *values, int start_index, int end_index) {
  int range_size = end_index - start_index;
  if (needs_sorting(range_size)) {
    int mid_point = (start_index + end_index) / 2;
    mergesort_range(values, start_index, mid_point);
    mergesort_range(values, mid_point, end_index);
    merge_ranges(values, start_index, mid_point, end_index);
  }
}

void merge_ranges(int *values, int start_index, int mid_point, int end_index) {
  int range_size = end_index - start_index;
  int *destination = (int*) calloc(range_size, sizeof(int));
  int first_index = start_index;
  int second_index = mid_point;
  int copy_index = 0;
  while (first_index < mid_point && second_index < end_index) {
    if (values[first_index] < values[second_index]) {
      destination[copy_index] = values[first_index];
      first_index++;
    } else {
      destination[copy_index] = values[second_index];
      second_index++;
    }
    copy_index++;
  }
  while (first_index < mid_point) {
    destination[copy_index] = values[first_index];
    copy_index++;
    first_index++;
  }
  while (second_index < end_index) {
    destination[copy_index] = values[second_index];
    copy_index++;
    second_index++;
  }
  int i;
  for (i = 0; i < range_size; i++) {
    values[i + start_index] = destination[i];
  }
  free(destination);
}

bool needs_sorting(int range_size) {
  return range_size >= 2;
}
