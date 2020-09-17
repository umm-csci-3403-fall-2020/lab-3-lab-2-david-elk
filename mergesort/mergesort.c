#include "mergesort.h"

void mergesort(int size, int *values) {
  mergesort_range(values, 0, size);
  return;
}

void mergesort_range(int *values, int start_index, int end_index) {
  int range_size = end_index - start_index;
  if (needs_sorting(range_size)) {
    int mid_point = (start_index + end_index) / 2;
  }
}
