#include <stdlib.h>

int maxChunksToSorted(int *arr, int arrSize) {
  int *st = malloc(arrSize * sizeof(int));
  int top = 0;

  for (int i = 0; i < arrSize; i++) {
    int n = arr[i];
    if (top == 0 || n > st[top - 1]) {
      st[top++] = n;
    } else {
      int mx = st[top - 1];
      top--;
      while (top > 0 && n <= st[top - 1])
        top--;
      st[top++] = mx;
    }
  }

  free(st);
  return top;
}
