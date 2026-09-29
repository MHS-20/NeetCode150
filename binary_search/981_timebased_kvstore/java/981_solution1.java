import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class TimeMap {
    private Map<String, List<int[]>> kv;
    private Map<String, List<String>> values;

    public TimeMap() {
        kv = new HashMap<>();
        values = new HashMap<>();
    }

    public void set(String key, String value, int timestamp) {
        kv.computeIfAbsent(key, k -> new ArrayList<>()).add(new int[] { timestamp });
        values.computeIfAbsent(key, k -> new ArrayList<>()).add(value);
    }

    public String get(String key, int timestamp) {
        if (!kv.containsKey(key))
            return "";

        List<int[]> times = kv.get(key);
        List<String> vals = values.get(key);
        int left = 0, right = times.size() - 1, resIdx = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int t = times.get(mid)[0];

            if (t == timestamp)
                return vals.get(mid);
            if (t > timestamp)
                right = mid - 1;
            else {
                resIdx = mid;
                left = mid + 1;
            }
        }

        return resIdx == -1 ? "" : vals.get(resIdx);
    }
}
