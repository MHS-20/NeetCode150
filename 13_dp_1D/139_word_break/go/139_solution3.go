package dp

func wordBreak(s string, wordDict []string) bool {
	n := len(s)
	dp := make([]bool, n+1)
	dp[0] = true

	for i := 1; i <= n; i++ {
		for _, w := range wordDict {
			l := len(w)
			// Does word w end exactly at position i?
			if l <= i && dp[i-l] && s[i-l:i] == w {
				dp[i] = true
				break
			}
		}
	}
	return dp[n]
}
