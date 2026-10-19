#include <stdlib.h>

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

int findKthLargest(int *nums, int numsSize, int k) {
  int *pq = malloc(k * sizeof(int)); // min-heap of the k largest
  int n = 0;

  for (int i = 0; i < numsSize; i++) {
    if (n < k) {
      pq[n] = nums[i];
      siftUp(pq, n++);
    } else if (nums[i] > pq[0]) {
      pq[0] = nums[i];
      siftDown(pq, n, 0);
    }
  }

  int res = pq[0];
  free(pq);
  return res;
}
