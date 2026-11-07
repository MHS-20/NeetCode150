#include <stdlib.h>

int *dailyTemperatures(int *temps, int n, int *returnSize) {
    int *res = calloc(n, sizeof(int));
    int *st = malloc(n * sizeof(int)); // indices with no warmer day yet
    int top = 0;

    for (int i = 0; i < n; i++) {
        while (top > 0 && temps[i] > temps[st[top - 1]]) {
            int j = st[--top];
            res[j] = i - j;
        }
        st[top++] = i;
    }
    free(st);
    *returnSize = n;
    return res;
}
