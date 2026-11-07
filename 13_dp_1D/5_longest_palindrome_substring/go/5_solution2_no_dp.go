package dp

// expand grows outward from the center (left, right) while the ends match.
// Returns the length of the palindrome found.
func expand(s string, left, right int) int {
	for left >= 0 && right < len(s) && s[left] == s[right] {
		left--
		right++
	}
	return right - left - 1
}

func longestPalindrome(s string) string {
	bestStart, bestLen := 0, 0

	for i := range len(s) {
		oddLen := expand(s, i, i)    // center on a character: "aba"
		evenLen := expand(s, i, i+1) // center between two characters: "abba"
		length := max(oddLen, evenLen)

		if length > bestLen {
			bestLen = length
			bestStart = i - (length-1)/2
		}
	}
	return s[bestStart : bestStart+bestLen]
}
