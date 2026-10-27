class Solution {
    public int countComponents(int n, int[][] edges) {
        int[] parent = new int[n + 1];
        int count = n;
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        for (int[] edge : edges) {
            int ra = find(parent, edge[0]);
            int rb = find(parent, edge[1]);
            if (ra != rb)
                count--;
            parent[rb] = ra;
        }
        return count;
    }

    private int find(int[] parent, int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
}
