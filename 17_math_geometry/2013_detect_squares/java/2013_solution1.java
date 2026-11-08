import java.util.HashMap;
import java.util.Map;

class DetectSquares {
    private final Map<Long, Integer> cnt = new HashMap<>();

    private static long key(int x, int y) {
        return ((long) x << 32) | y;
    }

    private int get(int x, int y) {
        return cnt.getOrDefault(key(x, y), 0);
    }

    public DetectSquares() {
    }

    public void add(int[] point) {
        cnt.merge(key(point[0], point[1]), 1, Integer::sum);
    }

    public int count(int[] point) {
        int x = point[0], y = point[1], res = 0;

        for (Map.Entry<Long, Integer> e : cnt.entrySet()) {
            int px = (int) (e.getKey() >> 32), py = (int) (long) e.getKey();
            if (px == x || Math.abs(px - x) != Math.abs(py - y))
                continue; // must be a diagonal corner with side length > 0
            res += e.getValue() * get(x, py) * get(px, y);
        }
        return res;
    }
}
