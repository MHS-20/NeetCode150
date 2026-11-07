import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int n : nums)
            freq.merge(n, 1, Integer::sum);

        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        for (Map.Entry<Integer, Integer> entry : freq.entrySet()) {
            minHeap.offer(new int[] { entry.getValue(), entry.getKey() });
            if (minHeap.size() > k)
                minHeap.poll();
        }

        int[] res = new int[k];
        for (int i = 0; i < k; i++)
            res[i] = minHeap.poll()[1];
        return res;
    }
}
