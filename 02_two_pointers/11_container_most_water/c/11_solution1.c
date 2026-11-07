int maxArea(int *height, int heightSize) {
    int left = 0, right = heightSize - 1, mx = 0;

    while (left < right) {
        int width = right - left;
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = h * width;
        if (area > mx) mx = area;

        if (height[left] > height[right]) right--;
        else left++;
    }

    return mx;
}
