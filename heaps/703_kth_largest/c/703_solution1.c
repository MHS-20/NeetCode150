#include <stdlib.h>

typedef struct {
  int *heap; // min-heap holding the k largest values
  int size;
  int cap;
} KthLargest;

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void siftUp(int *h, int i) {
  while (i > 0 && h[(i - 1) / 2] > h[i]) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
}

static void siftDown(int *h, int n, int i) {
  for (;;) {
    int min = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l] < h[min])
      min = l;
    if (r < n && h[r] < h[min])
      min = r;
    if (min == i)
      return;
    swap(&h[min], &h[i]);
    i = min;
  }
}

static void push(KthLargest *obj, int val) {
  obj->heap[obj->size] = val;
  siftUp(obj->heap, obj->size++);
  if (obj->size > obj->cap) {
    obj->heap[0] = obj->heap[--obj->size];
    siftDown(obj->heap, obj->size, 0);
  }
}

KthLargest *kthLargestCreate(int k, int *nums, int numsSize) {
  KthLargest *obj = malloc(sizeof(KthLargest));
  obj->heap = malloc((k + 1) * sizeof(int));
  obj->size = 0;
  obj->cap = k;
  for (int i = 0; i < numsSize; i++)
    push(obj, nums[i]);
  return obj;
}

int kthLargestAdd(KthLargest *obj, int val) {
  push(obj, val);
  return obj->heap[0];
}

void kthLargestFree(KthLargest *obj) {
  free(obj->heap);
  free(obj);
}
