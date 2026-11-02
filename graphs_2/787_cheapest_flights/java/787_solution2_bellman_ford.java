import java.util.Arrays;

class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        int[] prices = new int[n];
        Arrays.fill(prices, Integer.MAX_VALUE);
        prices[src] = 0;

        // Bellman-Ford limited to k + 1 rounds: round i allows i flights
        for (int round = 0; round <= k; round++) {
            int[] next = prices.clone(); // reads come from the previous round only
            for (int[] f : flights) {
                int from = f[0], to = f[1], price = f[2];
                if (prices[from] != Integer.MAX_VALUE && prices[from] + price < next[to])
                    next[to] = prices[from] + price;
            }
            prices = next;
        }

        return prices[dst] == Integer.MAX_VALUE ? -1 : prices[dst];
    }
}
