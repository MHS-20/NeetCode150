package main

func minWindow(s string, t string) string {
	var need [128]int
	for i := 0; i < len(t); i++ {
		need[t[i]]++
	}
	missing := len(t)

	bestStart, bestLen := 0, len(s)+1
	left := 0

	for right := 0; right < len(s); right++ {
		if need[s[right]] > 0 {
			missing-- // this char was still needed
		}
		need[s[right]]--

		for missing == 0 { // window is valid: try to shrink
			if right-left+1 < bestLen {
				bestStart, bestLen = left, right-left+1
			}
			need[s[left]]++
			if need[s[left]] > 0 {
				missing++ // we just removed a needed char
			}
			left++
		}
	}

	if bestLen > len(s) {
		return ""
	}
	return s[bestStart : bestStart+bestLen]
}
