package dp

func wordBreak(s string, wordDict []string) bool {
	n := len(s)
	words := make(map[string]bool, len(wordDict))
	for _, w := range wordDict {
		words[w] = true
	}
	dp := make([]bool, n+1)
	dp[0] = true // empty prefix is segmentable

	for i := 1; i <= n; i++ {
		for j := 0; j < i; j++ {
			if dp[j] && words[s[j:i]] {
				dp[i] = true
				break // one valid split is enough
			}
		}
	}
	return dp[n]
}
