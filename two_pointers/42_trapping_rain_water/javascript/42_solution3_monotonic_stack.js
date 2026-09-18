class Solution {
  trap(height) {
    const stack = [];
    let total = 0;

    for (let i = 0; i < height.length; i++) {
      while (stack.length > 0 && height[i] > height[stack[stack.length - 1]]) {
        const bottom = stack.pop();

        if (stack.length === 0) break;

        const left = stack[stack.length - 1];
        const width = i - left - 1;
        const depth = Math.min(height[left], height[i]) - height[bottom];
        total += width * depth;
      }

      stack.push(i);
    }

    return total;
  }
}
