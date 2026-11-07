import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

class Solution {
    public int networkDelayTime(int[][] times, int n, int k) {
        List<List<int[]>> adj = new ArrayList<>(); // node -> {neighbor, weight}
        for (int i = 0; i <= n; i++)
            adj.add(new ArrayList<>());
        for (int[] t : times)
            adj.get(t[0]).add(new int[] { t[1], t[2] });

        int[] dist = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]); // {dist, node}
        dist[k] = 0;
        pq.offer(new int[] { 0, k });

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int d = cur[0], u = cur[1];
            if (d > dist[u])
                continue; // stale entry
            for (int[] e : adj.get(u)) {
                int v = e[0], w = e[1];
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.offer(new int[] { dist[v], v });
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = Math.max(ans, dist[i]);
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
}
