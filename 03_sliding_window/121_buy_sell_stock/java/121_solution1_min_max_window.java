class Solution {
    public int maxProfit(int[] prices) {
        int mn = Integer.MAX_VALUE;
        int profit = 0;

        for (int p : prices) {
            mn = Math.min(mn, p);
            profit = Math.max(profit, p - mn);
        }

        return profit;
    }
}
