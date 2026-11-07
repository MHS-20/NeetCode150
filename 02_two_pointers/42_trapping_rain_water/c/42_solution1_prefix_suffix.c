#include <stdlib.h>

int trap(int *height, int heightSize) {
    if (heightSize == 0) {
        return 0;
    }

    int *leftMax = malloc(heightSize * sizeof(int));
    int *rightMax = malloc(heightSize * sizeof(int));

    leftMax[0] = height[0];
    for (int i = 1; i < heightSize; i++) {
        leftMax[i] = height[i] > leftMax[i - 1] ? height[i] : leftMax[i - 1];
    }

    rightMax[heightSize - 1] = height[heightSize - 1];
    for (int i = heightSize - 2; i >= 0; i--) {
        rightMax[i] = height[i] > rightMax[i + 1] ? height[i] : rightMax[i + 1];
    }

    int total = 0;
    for (int i = 0; i < heightSize; i++) {
        int level = leftMax[i] < rightMax[i] ? leftMax[i] : rightMax[i];
        total += level - height[i];
    }

    free(leftMax);
    free(rightMax);

    return total;
}
