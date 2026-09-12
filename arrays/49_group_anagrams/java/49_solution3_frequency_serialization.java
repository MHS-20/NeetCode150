import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> groups = new HashMap<>();

        for (String s : strs) {
            String key = serializeFrequency(s);
            groups.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(groups.values());
    }

    private String serializeFrequency(String s) {
        int[] alphabet = new int[26];
        for (char c : s.toCharArray())
            alphabet[c - 'a']++;

        StringBuilder key = new StringBuilder();
        for (int i = 0; i < 26; i++)
            key.append(alphabet[i]).append('#');
        return key.toString();
    }
}
