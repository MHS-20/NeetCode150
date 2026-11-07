class Solution {
    public int maxCoins(int[] nums) {
        int N = nums.length + 2;
        int[] a = new int[N]; // pad: [1, nums..., 1]
        a[0] = a[N - 1] = 1;
        System.arraycopy(nums, 0, a, 1, nums.length);

        int[][] dp = new int[N][N]; // len < 2 → 0 already

        for (int len = 2; len < N; len++) { // distance between walls
            for (int l = 0; l + len < N; l++) {
                int r = l + len;
                for (int k = l + 1; k < r; k++) {
                    dp[l][r] = Math.max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[k] * a[r]);
                }
            }
        }
        return dp[0][N - 1];
    }
}
