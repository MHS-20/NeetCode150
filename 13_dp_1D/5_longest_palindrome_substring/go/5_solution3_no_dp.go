package dp

func longestPalindrome(s string) string {
	bestStart, bestLen := 0, 0

	expand := func(l, r int) {
		// bounds first, so s[l] and s[r] are only read when valid
		for l >= 0 && r < len(s) && s[l] == s[r] {
			l--
			r++
		}
		// pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
		if length := r - l - 1; length > bestLen {
			bestStart, bestLen = l+1, length
		}
	}

	for i := 0; i < len(s); i++ {
		// odd-length palindromes, centered on s[i]
		expand(i, i)
		// even-length palindromes, centered between s[i] and s[i+1]
		expand(i, i+1)
	}

	return s[bestStart : bestStart+bestLen]
}
