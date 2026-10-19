static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void siftDown(int *h, int n, int i) {
  for (;;) {
    int max = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l] > h[max])
      max = l;
    if (r < n && h[r] > h[max])
      max = r;
    if (max == i)
      return;
    swap(&h[max], &h[i]);
    i = max;
  }
}

static void siftUp(int *h, int i) {
  while (i > 0 && h[(i - 1) / 2] < h[i]) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
}

static int pop(int *h, int *n) {
  int top = h[0];
  h[0] = h[--*n];
  siftDown(h, *n, 0);
  return top;
}

// uses stones itself as a max-heap
int lastStoneWeight(int *stones, int stonesSize) {
  int n = stonesSize;
  for (int i = n / 2 - 1; i >= 0; i--)
    siftDown(stones, n, i);

  while (n > 1) {
    int y = pop(stones, &n);
    int x = pop(stones, &n);
    if (y != x) {
      stones[n] = y - x;
      siftUp(stones, n++);
    }
  }

  return n == 0 ? 0 : stones[0];
}
