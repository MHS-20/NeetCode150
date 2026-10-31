#include <stdbool.h>
#include <stdlib.h>

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize) {
  (void)prerequisitesColSize; // always 2

  // unlocks in CSR form: course b's dependents are edges[start[b] .. start[b+1])
  int *start = calloc(numCourses + 1, sizeof(int));
  int *edges = malloc((prerequisitesSize ? prerequisitesSize : 1) * sizeof(int));
  int *remaining = calloc(numCourses, sizeof(int)); // prerequisites still missing
  for (int i = 0; i < prerequisitesSize; i++) {
    start[prerequisites[i][1] + 1]++;
    remaining[prerequisites[i][0]]++;
  }
  for (int u = 0; u < numCourses; u++)
    start[u + 1] += start[u];
  int *fill = malloc(numCourses * sizeof(int));
  for (int u = 0; u < numCourses; u++)
    fill[u] = start[u];
  for (int i = 0; i < prerequisitesSize; i++)
    edges[fill[prerequisites[i][1]]++] = prerequisites[i][0];
  free(fill);

  int *queue = malloc(numCourses * sizeof(int));
  int head = 0, tail = 0;
  for (int c = 0; c < numCourses; c++)
    if (remaining[c] == 0)
      queue[tail++] = c;

  while (head < tail) {
    int c = queue[head++];
    for (int e = start[c]; e < start[c + 1]; e++)
      if (--remaining[edges[e]] == 0)
        queue[tail++] = edges[e];
  }

  free(start);
  free(edges);
  free(remaining);
  free(queue);
  return tail == numCourses;
}
