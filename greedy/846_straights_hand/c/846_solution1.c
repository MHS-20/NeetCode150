#include <stdbool.h>
#include <stdlib.h>

static int cmpInt(const void *a, const void *b) {
  return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b);
}

bool isNStraightHand(int *hand, int handSize, int groupSize) {
  if (handSize % groupSize != 0)
    return false;

  // C has no ordered map: sort, then collapse into distinct values + counts
  qsort(hand, handSize, sizeof(int), cmpInt);
  int *vals = malloc(handSize * sizeof(int));
  int *cnt = malloc(handSize * sizeof(int));
  int m = 0;
  for (int i = 0; i < handSize; i++) {
    if (m > 0 && vals[m - 1] == hand[i]) {
      cnt[m - 1]++;
    } else {
      vals[m] = hand[i];
      cnt[m++] = 1;
    }
  }

  bool ok = true;
  for (int i = 0; i < m && ok; i++) {
    int c = cnt[i];
    if (c == 0)
      continue; // already used up by earlier groups
    for (int j = 0; j < groupSize; j++) {
      // missing value or too few copies: group can't be built
      if (i + j >= m || vals[i + j] != vals[i] + j || cnt[i + j] < c) {
        ok = false;
        break;
      }
      cnt[i + j] -= c;
    }
  }

  free(vals);
  free(cnt);
  return ok;
}
