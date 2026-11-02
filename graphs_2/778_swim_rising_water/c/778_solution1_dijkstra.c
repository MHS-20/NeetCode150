#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int elev, r, c;
} Entry;

static void push(Entry *heap, int *len, Entry e) {
  int i = (*len)++;
  while (i > 0 && e.elev < heap[(i - 1) / 2].elev) {
    heap[i] = heap[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  heap[i] = e;
}

static Entry pop(Entry *heap, int *len) {
  Entry top = heap[0], last = heap[--(*len)];
  int i = 0;
  for (;;) {
    int child = 2 * i + 1;
    if (child >= *len)
      break;
    if (child + 1 < *len && heap[child + 1].elev < heap[child].elev)
      child++;
    if (heap[child].elev >= last.elev)
      break;
    heap[i] = heap[child];
    i = child;
  }
  heap[i] = last;
  return top;
}

int swimInWater(int **grid, int gridSize, int *gridColSize) {
  (void)gridColSize; // square grid
  int n = gridSize;
  bool *visited = calloc(n * n, sizeof(bool));
  Entry *heap = malloc(n * n * sizeof(Entry)); // each cell is pushed once
  int len = 0;
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  push(heap, &len, (Entry){grid[0][0], 0, 0});
  visited[0] = true;
  int t = 0, ans = -1;

  while (len > 0) {
    Entry e = pop(heap, &len);
    if (e.elev > t)
      t = e.elev;
    if (e.r == n - 1 && e.c == n - 1) {
      ans = t;
      break;
    }

    for (int d = 0; d < 4; d++) {
      int nr = e.r + dirs[d][0], nc = e.c + dirs[d][1];
      if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr * n + nc])
        continue;
      visited[nr * n + nc] = true;
      push(heap, &len, (Entry){grid[nr][nc], nr, nc});
    }
  }

  free(visited);
  free(heap);
  return ans;
}
