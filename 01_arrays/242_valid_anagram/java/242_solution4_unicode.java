import java.util.HashMap;
import java.util.Map;

class Solution {
    public boolean isAnagram(String s, String t) {
        // charAt/toCharArray walk UTF-16 code units and can split surrogate
        // pairs for astral characters; codePoints() iterates full code points.
        int[] sPoints = s.codePoints().toArray();
        int[] tPoints = t.codePoints().toArray();

        if (sPoints.length != tPoints.length) {
            return false;
        }

        Map<Integer, Integer> counts = new HashMap<>();
        for (int cp : sPoints) {
            counts.merge(cp, 1, Integer::sum);
        }

        for (int cp : tPoints) {
            Integer remaining = counts.get(cp);
            if (remaining == null || remaining == 0) {
                return false;
            }
            counts.put(cp, remaining - 1);
        }

        return true;
    }
}
