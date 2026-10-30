#include <limits.h>
#include <stdlib.h>

int maxChunksToSorted(int *arr, int arrSize) {
  int *sufMin = malloc((arrSize + 1) * sizeof(int));
  sufMin[arrSize] = INT_MAX;
  for (int i = arrSize - 1; i >= 0; i--)
    sufMin[i] = arr[i] < sufMin[i + 1] ? arr[i] : sufMin[i + 1];

  int chunks = 0, prefMax = INT_MIN;
  for (int i = 0; i < arrSize; i++) {
    if (arr[i] > prefMax)
      prefMax = arr[i];
    if (prefMax <= sufMin[i + 1])
      chunks++; // valid cut after i (i = n-1 always counts)
  }

  free(sufMin);
  return chunks;
}
