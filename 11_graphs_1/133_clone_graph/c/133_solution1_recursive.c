#include <stdlib.h>

#include "node.h"

#define MAX_VAL 100 // node values are unique and in [1, 100]

static struct Node *dfs(struct Node *node, struct Node **clones) {
  if (!clones[node->val]) {
    struct Node *copy = malloc(sizeof *copy);
    copy->val = node->val;
    copy->numNeighbors = node->numNeighbors;
    copy->neighbors = malloc(node->numNeighbors * sizeof(struct Node *));
    clones[node->val] = copy; // register before recursing to break cycles
    for (int i = 0; i < node->numNeighbors; i++)
      copy->neighbors[i] = dfs(node->neighbors[i], clones);
  }

  return clones[node->val];
}

struct Node *cloneGraph(struct Node *s) {
  if (!s)
    return NULL;

  struct Node *clones[MAX_VAL + 1] = {0};
  return dfs(s, clones);
}
