import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int n : nums)
            freq.merge(n, 1, Integer::sum);

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        for (Map.Entry<Integer, Integer> entry : freq.entrySet())
            maxHeap.offer(new int[] { entry.getValue(), entry.getKey() });

        int[] res = new int[k];
        for (int i = 0; i < k; i++)
            res[i] = maxHeap.poll()[1];
        return res;
    }
}
