class Solution {
    public int maxChunksToSorted(int[] arr) {
        int[] st = new int[arr.length]; // max of each chunk, non-decreasing
        int top = 0;
        for (int x : arr) {
            int curMax = x;
            while (top > 0 && st[top - 1] > x)
                curMax = Math.max(curMax, st[--top]);
            st[top++] = curMax;
        }
        return top;
    }
}
