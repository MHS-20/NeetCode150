#pragma once

#include <stddef.h>

// Definition for a Node.
struct Node {
  int val;
  int numNeighbors;
  struct Node **neighbors;
};
