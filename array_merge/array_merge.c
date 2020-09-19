#include "array_merge.h"
#include "stdio.h"
#include "stdbool.h"

int* array_merge(int num_arrays, int* sizes, int** values) {
  // This is obviously broken. It has the right type, though, eh?
  for(i = 0; i < num_arrays; i++){
  	for(j = 0; j<sizes[i]; j++){
  		printf(values[i][j]);
  	}
  }
  return sizes;
}
