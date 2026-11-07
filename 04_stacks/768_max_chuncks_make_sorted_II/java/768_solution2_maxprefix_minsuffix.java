class Solution {
    public int maxChunksToSorted(int[] arr) {
        int n = arr.length;
        int[] sufMin = new int[n + 1];
        sufMin[n] = Integer.MAX_VALUE;
        for (int i = n - 1; i >= 0; i--)
            sufMin[i] = Math.min(sufMin[i + 1], arr[i]);

        int chunks = 0, prefMax = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            prefMax = Math.max(prefMax, arr[i]);
            if (prefMax <= sufMin[i + 1])
                chunks++; // valid cut after i (i = n-1 always counts)
        }
        return chunks;
    }
}
