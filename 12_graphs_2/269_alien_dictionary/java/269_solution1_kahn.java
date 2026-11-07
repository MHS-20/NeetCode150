import java.util.ArrayDeque;
import java.util.Queue;

class Solution {
    public String foreignDictionary(String[] words) {
        boolean[] seen = new boolean[26];
        boolean[][] edge = new boolean[26][26];
        int[] indeg = new int[26];
        int total = 0;

        for (String w : words)
            for (char c : w.toCharArray())
                if (!seen[c - 'a']) {
                    seen[c - 'a'] = true;
                    total++;
                }

        for (int i = 0; i + 1 < words.length; i++) {
            String a = words[i], b = words[i + 1];
            int len = Math.min(a.length(), b.length());
            int j = 0;
            while (j < len && a.charAt(j) == b.charAt(j))
                j++;

            if (j == len) {
                if (a.length() > b.length())
                    return ""; // b is a proper prefix of a: invalid
                continue;
            }
            int u = a.charAt(j) - 'a', v = b.charAt(j) - 'a';
            if (!edge[u][v]) { // avoid double-counting
                edge[u][v] = true;
                indeg[v]++;
            }
        }

        // Kahn's algorithm
        Queue<Integer> q = new ArrayDeque<>();
        for (int c = 0; c < 26; c++)
            if (seen[c] && indeg[c] == 0)
                q.offer(c);

        StringBuilder result = new StringBuilder();
        while (!q.isEmpty()) {
            int u = q.poll();
            result.append((char) ('a' + u));
            for (int v = 0; v < 26; v++)
                if (edge[u][v] && --indeg[v] == 0)
                    q.offer(v);
        }

        return result.length() == total ? result.toString() : "";
    }
}
