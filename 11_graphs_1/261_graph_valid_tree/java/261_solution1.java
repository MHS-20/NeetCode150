class Solution {
    public boolean validTree(int n, int[][] edges) {
        int count = n;
        int[] parent = new int[n + 1];
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        for (int[] edge : edges) {
            int ra = find(parent, edge[0]);
            int rb = find(parent, edge[1]);
            if (ra == rb)
                return false;
            else
                count--;
            parent[rb] = ra;
        }
        return count == 1;
    }

    private int find(int[] parent, int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
}
