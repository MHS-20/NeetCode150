package dp

type trieNode struct {
	children [26]*trieNode
	isWord   bool
}

func wordBreak(s string, wordDict []string) bool {
	// Build the trie from the dictionary
	root := &trieNode{}
	for _, w := range wordDict {
		node := root
		for i := 0; i < len(w); i++ {
			c := w[i] - 'a'
			if node.children[c] == nil {
				node.children[c] = &trieNode{}
			}
			node = node.children[c]
		}
		node.isWord = true
	}

	n := len(s)
	dp := make([]bool, n+1)
	dp[0] = true

	for j := 0; j < n; j++ {
		if !dp[j] {
			continue // only start a word where the prefix is segmentable
		}

		// Walk s and the trie together, starting at j
		node := root
		for k := j; k < n; k++ {
			node = node.children[s[k]-'a']
			if node == nil {
				break // no dictionary word continues this way
			}
			if node.isWord {
				dp[k+1] = true // s[j..k] is a word, so the first k+1 chars are segmentable
			}
		}
	}
	return dp[n]
}
