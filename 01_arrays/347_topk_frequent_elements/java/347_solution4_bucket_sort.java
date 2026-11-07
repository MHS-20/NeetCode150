import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int n : nums)
            freq.merge(n, 1, Integer::sum);

        List<List<Integer>> buckets = new ArrayList<>();
        for (int i = 0; i <= nums.length; i++)
            buckets.add(new ArrayList<>());

        for (Map.Entry<Integer, Integer> entry : freq.entrySet())
            buckets.get(entry.getValue()).add(entry.getKey());

        int[] res = new int[k];
        int idx = 0;
        for (int i = buckets.size() - 1; i >= 0 && idx < k; i--) {
            for (int val : buckets.get(i)) {
                res[idx++] = val;
                if (idx == k)
                    break;
            }
        }

        return res;
    }
}
