#include <stdbool.h>
#include <stdlib.h>

// adjacency in CSR form: node u's neighbors are edges[start[u] .. start[u+1])
static bool dfs(const int *start, const int *edges, int *state, int node,
                int *order, int *orderSize) {
  if (state[node] == 1)
    return false; // cycle
  if (state[node] == 2)
    return true;

  state[node] = 1;
  for (int e = start[node]; e < start[node + 1]; e++)
    if (!dfs(start, edges, state, edges[e], order, orderSize))
      return false;
  state[node] = 2;
  order[(*orderSize)++] = node;
  return true;
}

int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
  (void)prerequisitesColSize; // always 2

  int *start = calloc(numCourses + 1, sizeof(int));
  int *edges = malloc((prerequisitesSize ? prerequisitesSize : 1) * sizeof(int));
  for (int i = 0; i < prerequisitesSize; i++)
    start[prerequisites[i][0] + 1]++;
  for (int u = 0; u < numCourses; u++)
    start[u + 1] += start[u];
  int *fill = malloc(numCourses * sizeof(int));
  for (int u = 0; u < numCourses; u++)
    fill[u] = start[u];
  for (int i = 0; i < prerequisitesSize; i++)
    edges[fill[prerequisites[i][0]]++] = prerequisites[i][1];
  free(fill);

  int *state = calloc(numCourses, sizeof(int)); // 0 = unvisited, 1 = on path, 2 = done
  int *order = malloc(numCourses * sizeof(int));
  *returnSize = 0;
  for (int i = 0; i < numCourses; i++)
    if (!dfs(start, edges, state, i, order, returnSize)) {
      *returnSize = 0; // cycle: no valid order
      break;
    }

  free(start);
  free(edges);
  free(state);
  return order;
}
