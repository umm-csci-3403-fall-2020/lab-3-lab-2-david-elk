#include "../mergesort/mergesort.h"
#include "array_merge.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isUnique(int n, int indexCounter, int* tempArray){
  bool unique = true;
  int i;
  for(i = 0; i < indexCounter; i++){
	if(n == tempArray[i]){
  	  unique = false;
  	  return unique;
  	}
  }
  return unique;
}

int* array_merge(int num_arrays, int* sizes, int** values) {
  int i;
  int j;
  int k;
  int l;
  int tempCounter = 0;

  for(k = 0; k < num_arrays; k++ ) {
  	tempCounter = tempCounter + sizes[k];
  }

  int *tempArray = (int*) calloc(tempCounter, sizeof(int));

  int indexCounter = 0;
  for(i = 0; i < num_arrays; i++){
  	for(j = 0; j < sizes[i]; j++){
  		if(isUnique(values[i][j],indexCounter,tempArray)){
  			tempArray[indexCounter] = values[i][j];
  			indexCounter++;
  		}
  	}
  }

  int *finalArray = (int*) calloc(indexCounter + 1,sizeof(int));
  finalArray[0] = 0;
  for(l = 0; l < indexCounter; l++){
  	finalArray[l+1] = tempArray[l];
  }
  free(tempArray);
  mergesort(indexCounter + 1, finalArray);
  finalArray[0] = indexCounter;
  return finalArray;
}
