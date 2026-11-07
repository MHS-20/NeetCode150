import java.util.Arrays;

class Solution {
    public int minCostConnectPoints(int[][] points) {
        int n = points.length;
        int[] minCost = new int[n];
        boolean[] inTree = new boolean[n];
        Arrays.fill(minCost, Integer.MAX_VALUE);
        minCost[0] = 0;
        int cost = 0;

        for (int step = 0; step < n; step++) {
            // 1. Pick the cheapest point not yet in the tree
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!inTree[i] && (u == -1 || minCost[i] < minCost[u]))
                    u = i;

            // 2. Add it
            inTree[u] = true;
            cost += minCost[u];

            // 3. Update the outside points' best connection
            for (int i = 0; i < n; i++) {
                if (inTree[i])
                    continue;
                int dist = Math.abs(points[i][0] - points[u][0]) + Math.abs(points[i][1] - points[u][1]);
                minCost[i] = Math.min(minCost[i], dist);
            }
        }
        return cost;
    }
}
