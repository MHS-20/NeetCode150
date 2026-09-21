package main

func checkInclusion(s1 string, s2 string) bool {
	k := len(s1)
	var freq, wfreq [26]int
	for i := 0; i < k; i++ {
		freq[s1[i]-'a']++
	}

	// matches = number of the 26 letters whose window count equals freq
	matches := 0
	for i := 0; i < 26; i++ {
		if freq[i] == wfreq[i] {
			matches++ // empty window: letters absent from s1 already match
		}
	}

	// change the window count of a letter by delta, keeping `matches` in sync
	update := func(ch byte, delta int) {
		c := ch - 'a'
		if wfreq[c] == freq[c] {
			matches-- // was matching, about to change
		}
		wfreq[c] += delta
		if wfreq[c] == freq[c] {
			matches++ // matches now
		}
	}

	for right := 0; right < len(s2); right++ {
		update(s2[right], +1) // char enters
		if right >= k {
			update(s2[right-k], -1) // char leaves
		}
		if matches == 26 {
			return true
		}
	}
	return false
}
