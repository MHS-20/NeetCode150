import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> unlocks = new ArrayList<>(numCourses); // b -> courses that need b
        for (int i = 0; i < numCourses; i++)
            unlocks.add(new ArrayList<>());
        int[] remaining = new int[numCourses]; // prerequisites still missing

        for (int[] p : prerequisites) {
            int a = p[0], b = p[1];
            unlocks.get(b).add(a);
            remaining[a]++;
        }

        Queue<Integer> q = new ArrayDeque<>();
        for (int c = 0; c < numCourses; c++)
            if (remaining[c] == 0)
                q.add(c);

        int taken = 0;
        while (!q.isEmpty()) {
            int c = q.poll();
            taken++;

            for (int next : unlocks.get(c))
                if (--remaining[next] == 0)
                    q.add(next);
        }

        return taken == numCourses;
    }
}
