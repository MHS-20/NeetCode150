class Solution {
    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        int[] parent = new int[n + 1];
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        for (int[] edge : edges) {
            int ra = find(parent, edge[0]);
            int rb = find(parent, edge[1]);
            if (ra == rb)
                return edge;
            parent[rb] = ra;
        }
        return new int[0];
    }

    private int find(int[] parent, int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
}
