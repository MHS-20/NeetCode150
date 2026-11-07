import java.util.Arrays;

class Solution {
    private int[] memo;

    private int ways(int i) {
        if (i <= 2)
            return i; // ways(1) = 1, ways(2) = 2
        if (memo[i] != -1)
            return memo[i];
        return memo[i] = ways(i - 1) + ways(i - 2);
    }

    public int climbStairs(int n) {
        memo = new int[n + 1];
        Arrays.fill(memo, -1);
        return ways(n);
    }
}
