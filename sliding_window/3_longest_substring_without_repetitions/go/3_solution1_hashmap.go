package main

func lengthOfLongestSubstring(s string) int {
	lastSeen := make(map[byte]int)
	maxLen, left := 0, 0

	for right := 0; right < len(s); right++ {
		c := s[right]

		if idx, ok := lastSeen[c]; ok && idx >= left {
			left = idx + 1
		}

		lastSeen[c] = right

		if length := right - left + 1; length > maxLen {
			maxLen = length
		}
	}

	return maxLen
}
