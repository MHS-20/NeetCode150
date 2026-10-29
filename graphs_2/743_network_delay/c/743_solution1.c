#include <limits.h>
#include <stdlib.h>

typedef struct {
  int d, node;
} Item;

typedef struct Edge {
  int to, w;
  struct Edge *next;
} Edge;

static void swap(Item *a, Item *b) {
  Item t = *a;
  *a = *b;
  *b = t;
}

static void push(Item *heap, int *size, Item x) {
  int i = (*size)++;
  heap[i] = x;
  while (i > 0 && heap[(i - 1) / 2].d > heap[i].d) {
    swap(&heap[(i - 1) / 2], &heap[i]);
    i = (i - 1) / 2;
  }
}

static Item pop(Item *heap, int *size) {
  Item top = heap[0];
  heap[0] = heap[--(*size)];
  int i = 0;
  for (;;) {
    int s = i, l = 2 * i + 1, r = l + 1;
    if (l < *size && heap[l].d < heap[s].d)
      s = l;
    if (r < *size && heap[r].d < heap[s].d)
      s = r;
    if (s == i)
      break;
    swap(&heap[s], &heap[i]);
    i = s;
  }
  return top;
}

int networkDelayTime(int **times, int timesSize, int *timesColSize, int n,
                     int k) {
  (void)timesColSize;
  // adjacency lists as linked lists; one edge node per input edge
  Edge **adj = calloc(n + 1, sizeof(Edge *));
  Edge *pool = malloc(timesSize * sizeof(Edge));
  for (int i = 0; i < timesSize; i++) {
    pool[i] = (Edge){times[i][1], times[i][2], adj[times[i][0]]};
    adj[times[i][0]] = &pool[i];
  }

  int *dist = malloc((n + 1) * sizeof(int));
  for (int i = 0; i <= n; i++)
    dist[i] = INT_MAX;
  // each successful relaxation pushes once, so at most timesSize + 1 entries
  Item *heap = malloc((timesSize + 1) * sizeof(Item));
  int size = 0;
  dist[k] = 0;
  push(heap, &size, (Item){0, k});

  while (size > 0) {
    Item cur = pop(heap, &size);
    if (cur.d > dist[cur.node])
      continue; // stale entry
    for (Edge *e = adj[cur.node]; e; e = e->next) {
      if (cur.d + e->w < dist[e->to]) {
        dist[e->to] = cur.d + e->w;
        push(heap, &size, (Item){dist[e->to], e->to});
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (dist[i] > ans)
      ans = dist[i];

  free(adj);
  free(pool);
  free(dist);
  free(heap);
  return ans == INT_MAX ? -1 : ans;
}
