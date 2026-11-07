import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        int n = s.length();
        Set<String> words = new HashSet<>(wordDict);

        int maxLen = 0;
        for (String w : wordDict)
            maxLen = Math.max(maxLen, w.length());

        boolean[] dp = new boolean[n + 1];
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            // A piece longer than maxLen can't be a word, so start j no earlier than
            // i - maxLen
            for (int j = Math.max(0, i - maxLen); j < i; j++) {
                if (dp[j] && words.contains(s.substring(j, i))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
}
