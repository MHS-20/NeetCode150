import java.util.HashMap;
import java.util.Map;

class Solution {
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }

        Map<Character, Integer> counts = new HashMap<>();
        for (char c : s.toCharArray()) {
            counts.merge(c, 1, Integer::sum);
        }

        for (char c : t.toCharArray()) {
            Integer remaining = counts.get(c);
            if (remaining == null || remaining == 0) {
                return false;
            }
            counts.put(c, remaining - 1);
        }

        return true;
    }
}
