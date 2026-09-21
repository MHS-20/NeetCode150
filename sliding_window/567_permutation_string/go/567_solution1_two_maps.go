package main

func checkInclusion(s1 string, s2 string) bool {
	k := len(s1)
	freq, wfreq := map[byte]int{}, map[byte]int{}
	for i := 0; i < k; i++ {
		freq[s1[i]]++
	}

	need := len(freq) // distinct letters in s1, fixed from here on
	matches := 0      // letters of s1 whose window count equals freq

	// change the window count of c by delta, keeping `matches` in sync
	update := func(c byte, delta int) {
		target, ok := freq[c]
		if !ok {
			return // not in s1: irrelevant
		}
		if wfreq[c] == target {
			matches-- // was matching, about to change
		}
		wfreq[c] += delta
		if wfreq[c] == target {
			matches++ // matches now
		}
	}

	for right := 0; right < len(s2); right++ {
		update(s2[right], +1) // char enters
		if right >= k {
			update(s2[right-k], -1) // char leaves
		}
		if matches == need {
			return true
		}
	}
	return false
}
