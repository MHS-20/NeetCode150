import java.util.Arrays;

class Solution {
    private int f(int l, int r, int[] a, int[][] dp) {
        if (r - l < 2)
            return 0; // nothing strictly between l and r
        if (dp[l][r] != -1)
            return dp[l][r];

        int best = 0;
        for (int k = l + 1; k < r; k++) { // k = last balloon burst in (l, r)
            int coins = a[l] * a[k] * a[r] + f(l, k, a, dp) + f(k, r, a, dp);
            best = Math.max(best, coins);
        }
        return dp[l][r] = best;
    }

    public int maxCoins(int[] nums) {
        int N = nums.length + 2;
        int[] a = new int[N]; // pad: [1, nums..., 1]
        a[0] = a[N - 1] = 1;
        System.arraycopy(nums, 0, a, 1, nums.length);

        int[][] dp = new int[N][N];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return f(0, N - 1, a, dp);
    }
}
