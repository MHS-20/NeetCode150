#include <stdlib.h>

#include "node.h"

#define MAX_VAL 100 // node values are unique and in [1, 100]

static struct Node *newNode(const struct Node *src) {
  struct Node *copy = malloc(sizeof *copy);
  copy->val = src->val;
  copy->numNeighbors = src->numNeighbors;
  copy->neighbors = malloc(src->numNeighbors * sizeof(struct Node *));
  return copy;
}

struct Node *cloneGraph(struct Node *s) {
  if (!s)
    return NULL;

  struct Node *clones[MAX_VAL + 1] = {0};
  struct Node *pending[MAX_VAL]; // each node is pushed once
  int top = 0;
  clones[s->val] = newNode(s);
  pending[top++] = s;

  while (top > 0) {
    struct Node *cur = pending[--top];
    for (int i = 0; i < cur->numNeighbors; i++) {
      struct Node *nb = cur->neighbors[i];
      if (!clones[nb->val]) {
        clones[nb->val] = newNode(nb);
        pending[top++] = nb;
      }
      clones[cur->val]->neighbors[i] = clones[nb->val];
    }
  }
  return clones[s->val];
}
