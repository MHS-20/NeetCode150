import java.util.ArrayDeque;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Queue;

class Solution {
    public int leastInterval(char[] tasks, int n) {
        int[] arr = new int[26];
        for (char ch : tasks)
            arr[ch - 'A']++;

        // remaining counts
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for (int c : arr)
            if (c > 0)
                pq.offer(c);

        Queue<int[]> timer = new ArrayDeque<>(); // {count, nextTime}
        int time = 0;

        while (!pq.isEmpty() || !timer.isEmpty()) {
            if (!timer.isEmpty() && timer.peek()[1] <= time)
                pq.offer(timer.poll()[0]);

            if (!pq.isEmpty()) {
                int count = pq.poll() - 1;
                if (count > 0)
                    timer.offer(new int[] {count, time + n + 1});
            }

            time++;
        }

        return time;
    }
}
