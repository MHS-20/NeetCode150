import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Queue;

class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        List<List<int[]>> adj = new ArrayList<>(); // from -> {to, price}
        for (int i = 0; i < n; i++)
            adj.add(new ArrayList<>());
        for (int[] f : flights)
            adj.get(f[0]).add(new int[] { f[1], f[2] });

        int[] prices = new int[n];
        Arrays.fill(prices, Integer.MAX_VALUE);
        Queue<int[]> q = new ArrayDeque<>(); // {city, cost so far}
        prices[src] = 0;
        q.offer(new int[] { src, 0 });

        // BFS by level, one level per flight (at most k + 1 levels)
        for (int flightsUsed = 0; flightsUsed <= k && !q.isEmpty(); flightsUsed++) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int[] cur = q.poll();
                int c = cur[0], p = cur[1];
                for (int[] e : adj.get(c)) {
                    int next = e[0], price = e[1];
                    if (p + price < prices[next]) {
                        prices[next] = p + price;
                        q.offer(new int[] { next, p + price });
                    }
                }
            }
        }

        return prices[dst] == Integer.MAX_VALUE ? -1 : prices[dst];
    }
}
