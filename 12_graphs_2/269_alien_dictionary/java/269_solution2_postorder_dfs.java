class Solution {
    private final boolean[] seen = new boolean[26];
    private final boolean[][] edge = new boolean[26][26];
    private final int[] state = new int[26]; // 0 = unvisited, 1 = visiting, 2 = done
    private final StringBuilder result = new StringBuilder();

    // Returns false if a cycle is found
    private boolean dfs(int u) {
        state[u] = 1;
        for (int v = 0; v < 26; v++) {
            if (!edge[u][v])
                continue;
            if (state[v] == 1)
                return false; // back edge: cycle
            if (state[v] == 0 && !dfs(v))
                return false; // propagate failure
        }
        state[u] = 2;
        result.append((char) ('a' + u)); // post-order
        return true;
    }

    public String foreignDictionary(String[] words) {
        // 1. Register every letter
        for (String w : words)
            for (char c : w.toCharArray())
                seen[c - 'a'] = true;

        // 2. Build edges (no in-degree needed)
        for (int i = 0; i + 1 < words.length; i++) {
            String a = words[i], b = words[i + 1];
            int len = Math.min(a.length(), b.length());
            int j = 0;
            while (j < len && a.charAt(j) == b.charAt(j))
                j++;

            if (j == len) {
                if (a.length() > b.length())
                    return "";
                continue;
            }
            edge[a.charAt(j) - 'a'][b.charAt(j) - 'a'] = true; // duplicates are harmless here
        }

        // 3. DFS from every unvisited letter
        for (int c = 0; c < 26; c++)
            if (seen[c] && state[c] == 0 && !dfs(c))
                return "";

        // 4. Post-order is reversed topological order
        return result.reverse().toString();
    }
}
