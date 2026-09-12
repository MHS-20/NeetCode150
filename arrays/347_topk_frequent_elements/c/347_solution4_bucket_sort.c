#include <stdlib.h>

int *topKFrequent(int *nums, int numsSize, int k, int *returnSize) {
  int *keys = (int *)malloc(numsSize * sizeof(int));
  int *counts = (int *)malloc(numsSize * sizeof(int));
  int uniqueCount = 0;

  for (int i = 0; i < numsSize; i++) {
    int found = -1;
    for (int j = 0; j < uniqueCount; j++) {
      if (keys[j] == nums[i]) {
        found = j;
        break;
      }
    }

    if (found == -1) {
      keys[uniqueCount] = nums[i];
      counts[uniqueCount] = 1;
      uniqueCount++;
    } else {
      counts[found]++;
    }
  }

  int **buckets = (int **)calloc(numsSize + 1, sizeof(int *));
  int *bucketSizes = (int *)calloc(numsSize + 1, sizeof(int));
  int *bucketCap = (int *)calloc(numsSize + 1, sizeof(int));

  for (int i = 0; i < uniqueCount; i++) {
    int cnt = counts[i];
    if (bucketSizes[cnt] == bucketCap[cnt]) {
      bucketCap[cnt] = bucketCap[cnt] == 0 ? 4 : bucketCap[cnt] * 2;
      buckets[cnt] = (int *)realloc(buckets[cnt], bucketCap[cnt] * sizeof(int));
    }
    buckets[cnt][bucketSizes[cnt]++] = keys[i];
  }

  int *result = (int *)malloc(k * sizeof(int));
  int idx = 0;
  for (int cnt = numsSize; cnt >= 0 && idx < k; cnt--) {
    for (int j = 0; j < bucketSizes[cnt] && idx < k; j++) {
      result[idx++] = buckets[cnt][j];
    }
  }

  for (int i = 0; i <= numsSize; i++)
    free(buckets[i]);
  free(buckets);
  free(bucketSizes);
  free(bucketCap);
  free(keys);
  free(counts);

  *returnSize = k;
  return result;
}
