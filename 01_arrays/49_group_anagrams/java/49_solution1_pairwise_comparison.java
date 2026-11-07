import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        List<List<String>> result = new ArrayList<>();

        for (String s : strs) {
            boolean placed = false;
            for (List<String> group : result) {
                if (isAnagram(s, group.get(0))) {
                    group.add(s);
                    placed = true;
                    break;
                }
            }

            if (!placed) {
                List<String> group = new ArrayList<>();
                group.add(s);
                result.add(group);
            }
        }

        return result;
    }

    private boolean isAnagram(String s, String t) {
        if (s.length() != t.length())
            return false;

        Map<Character, Integer> freq = new HashMap<>();
        for (char c : s.toCharArray())
            freq.merge(c, 1, Integer::sum);
        for (char c : t.toCharArray()) {
            int count = freq.merge(c, -1, Integer::sum);
            if (count < 0)
                return false;
        }
        return true;
    }
}
