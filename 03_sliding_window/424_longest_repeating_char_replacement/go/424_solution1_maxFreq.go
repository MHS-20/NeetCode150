package main

func characterReplacement(s string, k int) int {
	reps := make(map[byte]int)
	left := 0
	maxLen := k
	maxFreq := 0

	for right := 0; right < len(s); right++ {
		c := s[right]
		reps[c]++
		if reps[c] > maxFreq {
			maxFreq = reps[c]
		}

		if right-left-maxFreq >= k {
			reps[s[left]]--
			left++
		}

		if length := right - left + 1; length > maxLen {
			maxLen = length
		}
	}

	return maxLen
}
