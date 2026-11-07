static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void siftUp(int *h, int i) {
  while (i > 0 && h[(i - 1) / 2] < h[i]) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
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

static void push(int *h, int *n, int val) {
  h[*n] = val;
  siftUp(h, (*n)++);
}

static int pop(int *h, int *n) {
  int top = h[0];
  h[0] = h[--*n];
  siftDown(h, *n, 0);
  return top;
}

int leastInterval(char *tasks, int tasksSize, int n) {
  int arr[26] = {0};
  for (int i = 0; i < tasksSize; i++)
    arr[tasks[i] - 'A']++;

  int pq[26], pqSize = 0; // max-heap of remaining counts
  for (int i = 0; i < 26; i++)
    if (arr[i] > 0)
      push(pq, &pqSize, arr[i]);

  // ring buffer of {count, nextTime}; at most 26 tasks cool down at once
  int timer[26][2], head = 0, timerSize = 0;
  int time = 0;

  while (pqSize > 0 || timerSize > 0) {
    if (timerSize > 0 && timer[head][1] <= time) {
      push(pq, &pqSize, timer[head][0]);
      head = (head + 1) % 26;
      timerSize--;
    }

    if (pqSize > 0) {
      int count = pop(pq, &pqSize) - 1;
      if (count > 0) {
        int tail = (head + timerSize++) % 26;
        timer[tail][0] = count;
        timer[tail][1] = time + n + 1;
      }
    }

    time++;
  }

  return time;
}
