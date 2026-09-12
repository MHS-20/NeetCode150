#include <stdlib.h>

typedef struct {
  int val;
  int cnt;
} HeapItem;

static void swap(HeapItem *a, HeapItem *b) {
  HeapItem tmp = *a;
  *a = *b;
  *b = tmp;
}

static void siftUp(HeapItem *heap, int i) {
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (heap[parent].cnt >= heap[i].cnt)
      break;
    swap(&heap[parent], &heap[i]);
    i = parent;
  }
}

static void siftDown(HeapItem *heap, int size, int i) {
  while (1) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && heap[left].cnt > heap[largest].cnt)
      largest = left;
    if (right < size && heap[right].cnt > heap[largest].cnt)
      largest = right;
    if (largest == i)
      break;
    swap(&heap[i], &heap[largest]);
    i = largest;
  }
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

  HeapItem *maxHeap = (HeapItem *)malloc(uniqueCount * sizeof(HeapItem));
  int heapSize = 0;
  for (int i = 0; i < uniqueCount; i++) {
    maxHeap[heapSize].val = keys[i];
    maxHeap[heapSize].cnt = counts[i];
    siftUp(maxHeap, heapSize);
    heapSize++;
  }

  int *result = (int *)malloc(k * sizeof(int));
  for (int i = 0; i < k; i++) {
    result[i] = maxHeap[0].val;
    heapSize--;
    maxHeap[0] = maxHeap[heapSize];
    siftDown(maxHeap, heapSize, 0);
  }

  free(keys);
  free(counts);
  free(maxHeap);

  *returnSize = k;
  return result;
}
