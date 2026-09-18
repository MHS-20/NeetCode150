#include <stdlib.h>

int trap(int *height, int heightSize) {
    if (heightSize == 0) {
        return 0;
    }

    int *stack = malloc(heightSize * sizeof(int));
    int top = 0;
    int total = 0;

    for (int i = 0; i < heightSize; i++) {
        while (top > 0 && height[i] > height[stack[top - 1]]) {
            int bottom = stack[--top];

            if (top == 0) {
                break;
            }

            int left = stack[top - 1];
            int width = i - left - 1;
            int limit = height[left] < height[i] ? height[left] : height[i];
            total += width * (limit - height[bottom]);
        }

        stack[top++] = i;
    }

    free(stack);

    return total;
}
