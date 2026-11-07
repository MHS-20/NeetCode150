#include <stdbool.h>

bool mergeTriplets(int **triplets, int tripletsSize, int *tripletsColSize,
                   int *target, int targetSize) {
  (void)tripletsColSize; // always 3
  (void)targetSize;      // always 3
  bool found[3] = {false, false, false};

  for (int k = 0; k < tripletsSize; k++) {
    int *t = triplets[k];
    if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2])
      continue;
    for (int i = 0; i < 3; i++)
      if (t[i] == target[i])
        found[i] = true;
  }

  return found[0] && found[1] && found[2];
}
