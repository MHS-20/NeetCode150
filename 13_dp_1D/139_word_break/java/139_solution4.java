import java.util.List;

class Solution {
    private static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        boolean isWord = false;
    }

    public boolean wordBreak(String s, List<String> wordDict) {
        // Build the trie from the dictionary
        TrieNode root = new TrieNode();
        for (String w : wordDict) {
            TrieNode node = root;
            for (char c : w.toCharArray()) {
                if (node.children[c - 'a'] == null)
                    node.children[c - 'a'] = new TrieNode();
                node = node.children[c - 'a'];
            }
            node.isWord = true;
        }

        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;

        for (int j = 0; j < n; j++) {
            if (!dp[j])
                continue; // only start a word where the prefix is segmentable

            // Walk s and the trie together, starting at j
            TrieNode node = root;
            for (int k = j; k < n; k++) {
                node = node.children[s.charAt(k) - 'a'];
                if (node == null)
                    break; // no dictionary word continues this way
                if (node.isWord)
                    dp[k + 1] = true; // s[j..k] is a word, so the first k+1 chars are segmentable
            }
        }
        return dp[n];
    }
}
