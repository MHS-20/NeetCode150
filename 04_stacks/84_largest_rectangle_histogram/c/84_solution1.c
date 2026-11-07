#include <stdlib.h>

int largestRectangleArea(int *heights, int n) {
    int *st = malloc(n * sizeof(int)); // indices of increasing heights
    int top = 0, best = 0;

    for (int i = 0; i <= n; i++) {
        int h = i < n ? heights[i] : 0; // sentinel flushes the stack
        while (top > 0 && heights[st[top - 1]] > h) {
            int height = heights[st[--top]];
            int prev = top ? st[top - 1] : -1;
            int area = height * (i - prev - 1);
            if (area > best)
                best = area;
        }
        st[top++] = i;
    }
    free(st);
    return best;
}
