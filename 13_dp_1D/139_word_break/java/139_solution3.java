import java.util.List;

class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (String w : wordDict) {
                int len = w.length();
                // Does word w end exactly at position i?
                if (len <= i && dp[i - len] && s.startsWith(w, i - len)) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
}
