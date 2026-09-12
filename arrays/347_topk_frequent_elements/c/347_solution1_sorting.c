#include <stdlib.h>

typedef struct {
  int val;
  int cnt;
} FreqPair;

static int cmpFreqDesc(const void *a, const void *b) {
  return ((FreqPair *)b)->cnt - ((FreqPair *)a)->cnt;
}

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

  FreqPair *pairs = (FreqPair *)malloc(uniqueCount * sizeof(FreqPair));
  for (int i = 0; i < uniqueCount; i++) {
    pairs[i].val = keys[i];
    pairs[i].cnt = counts[i];
  }

  qsort(pairs, uniqueCount, sizeof(FreqPair), cmpFreqDesc);

  int *result = (int *)malloc(k * sizeof(int));
  for (int i = 0; i < k; i++)
    result[i] = pairs[i].val;

  free(keys);
  free(counts);
  free(pairs);

  *returnSize = k;
  return result;
}
