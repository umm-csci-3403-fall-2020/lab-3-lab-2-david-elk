#include <gtest/gtest.h>

#include "array_merge.h"

void arrays_match(int size, int a[], int b[]) {
  int i;

  for (i=0; i<size; ++i) {
    ASSERT_EQ(b[i], a[i]);
  }
}

TEST(ArrayMerge, Handle_empty_list) {
  int* a[] = { };
  int sizes[] = { };
  int expected[] = { 0 };
  int* result;

  result = array_merge(0, sizes,  a);
  arrays_match(1, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_singleton_list) {
  int num_arrays = 1;
  int sizes[] = { 1 };
  int a0[] = { 5 };
  int* a[] = { a0 };
  int expected[] = { 1, 5 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(2, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_one_longer_list) {
  int num_arrays = 1;
  int sizes[] = { 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int* a[] = { a0 };
  int expected[] = { 7, 0, 2, 3, 5, 6, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_multiple_copies_of_longer_list) {
  int num_arrays = 10;
  int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int* a[] = { a0, a0, a0, a0, a0, a0, a0, a0, a0, a0 };
  int expected[] = { 7, 0, 2, 3, 5, 6, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_multiple_copies_of_longer_list_different_orders) {
  int num_arrays = 9;
  int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int a1[] = { 5, 8, 9, 3, 2, 0, 6, 3, 2, 0 };
  int a2[] = { 8, 5, 0, 2, 3, 0, 2, 3, 6, 9 };
  int* a[] = { a0, a1, a2, a0, a1, a2, a0, a1, a2 };
  int expected[] = { 7, 0, 2, 3, 5, 6, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_different_sizes) {
  int num_arrays = 11;
  int sizes[num_arrays];
  int* a[num_arrays];
  int expected[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int* result;
  int i, j;

  for (i=0; i<num_arrays; ++i) {
    sizes[i] = i;
    a[i] = (int*) calloc(i, sizeof(int));
    for (j=0; j<i; ++j) {
      a[i][j] = j;
    }
  }

  result = array_merge(num_arrays, sizes, a);
  arrays_match(11, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_different_sizes_reversed) {
  int num_arrays = 11;
  int sizes[num_arrays];
  int* a[num_arrays];
  int expected[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int* result;
  int i, j;

  for (i=num_arrays-1; i>=0; --i) {
    sizes[i] = i;
    a[i] = (int*) calloc(i, sizeof(int));
    for (j=0; j<i; ++j) {
      a[i][j] = j;
    }
  }

  result = array_merge(num_arrays, sizes, a);
  arrays_match(11, result, expected);
  free(result);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
