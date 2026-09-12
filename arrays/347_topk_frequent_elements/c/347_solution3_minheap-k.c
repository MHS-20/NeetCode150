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
    if (heap[parent].cnt <= heap[i].cnt)
      break;
    swap(&heap[parent], &heap[i]);
    i = parent;
  }
}

static void siftDown(HeapItem *heap, int size, int i) {
  while (1) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && heap[left].cnt < heap[smallest].cnt)
      smallest = left;
    if (right < size && heap[right].cnt < heap[smallest].cnt)
      smallest = right;
    if (smallest == i)
      break;
    swap(&heap[i], &heap[smallest]);
    i = smallest;
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

  HeapItem *minHeap = (HeapItem *)malloc((k + 1) * sizeof(HeapItem));
  int heapSize = 0;

  for (int i = 0; i < uniqueCount; i++) {
    minHeap[heapSize].val = keys[i];
    minHeap[heapSize].cnt = counts[i];
    siftUp(minHeap, heapSize);
    heapSize++;

    if (heapSize > k) {
      heapSize--;
      minHeap[0] = minHeap[heapSize];
      siftDown(minHeap, heapSize, 0);
    }
  }

  int *result = (int *)malloc(heapSize * sizeof(int));
  for (int i = 0; i < heapSize; i++)
    result[i] = minHeap[i].val;

  free(keys);
  free(counts);
  free(minHeap);

  *returnSize = heapSize;
  return result;
}
