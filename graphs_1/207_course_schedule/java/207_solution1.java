import java.util.ArrayList;
import java.util.List;

class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adjacency = new ArrayList<>(numCourses);
        for (int i = 0; i < numCourses; i++)
            adjacency.add(new ArrayList<>());
        for (int[] p : prerequisites)
            adjacency.get(p[0]).add(p[1]);

        int[] state = new int[numCourses]; // 0 = unvisited, 1 = on path, 2 = done
        for (int i = 0; i < numCourses; i++)
            if (!dfs(adjacency, state, i))
                return false;
        return true;
    }

    private boolean dfs(List<List<Integer>> adjacency, int[] state, int node) {
        if (state[node] == 1)
            return false; // back on the current path: cycle
        if (state[node] == 2)
            return true; // already fully explored

        state[node] = 1;
        for (int next : adjacency.get(node))
            if (!dfs(adjacency, state, next))
                return false;
        state[node] = 2;
        return true;
    }
}
