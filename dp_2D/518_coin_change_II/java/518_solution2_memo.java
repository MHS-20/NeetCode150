import java.util.Arrays;

class Solution {
    private int f(int i, int x, int[] coins, int[][] dp) {
        if (x == 0)
            return 1; // made the amount
        if (i == coins.length)
            return 0; // out of coins
        if (dp[i][x] != -1)
            return dp[i][x];

        int skip = f(i + 1, x, coins, dp); // never use coin i again
        int take = 0;
        if (coins[i] <= x)
            take = f(i, x - coins[i], coins, dp); // use coin i, stay at i (reuse allowed)

        return dp[i][x] = skip + take;
    }

    public int change(int amount, int[] coins) {
        int[][] dp = new int[coins.length][amount + 1];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return f(0, amount, coins, dp);
    }
}
