#include <stdlib.h>

int maxChunksToSorted(int *arr, int arrSize) {
  int *st = malloc(arrSize * sizeof(int)); // max of each chunk, non-decreasing
  int top = 0;
  for (int i = 0; i < arrSize; i++) {
    int curMax = arr[i];
    while (top > 0 && st[top - 1] > arr[i]) {
      if (st[top - 1] > curMax)
        curMax = st[top - 1];
      top--;
    }
    st[top++] = curMax;
  }
  free(st);
  return top;
}
