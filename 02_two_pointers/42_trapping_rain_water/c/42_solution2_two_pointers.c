int trap(int *height, int heightSize) {
    if (heightSize == 0) {
        return 0;
    }

    int left = 0, right = heightSize - 1;
    int leftMax = height[left], rightMax = height[right];
    int total = 0;

    while (left < right) {
        if (leftMax < rightMax) {
            left++;
            if (height[left] > leftMax) leftMax = height[left];
            total += leftMax - height[left];
        } else {
            right--;
            if (height[right] > rightMax) rightMax = height[right];
            total += rightMax - height[right];
        }
    }

    return total;
}
