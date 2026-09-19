package main

func checkInclusion(s1 string, s2 string) bool {
	if len(s1) > len(s2) {
		return false
	}

	var s1freq, windowfreq [26]int
	for i := 0; i < len(s1); i++ {
		s1freq[s1[i]-'a']++
		windowfreq[s2[i]-'a']++
	}

	match := 0
	for i := 0; i < 26; i++ {
		if s1freq[i] == windowfreq[i] {
			match++
		}
	}
	if match == 26 {
		return true
	}

	left := 0
	for right := len(s1); right < len(s2); right++ {
		r := s2[right] - 'a'
		l := s2[left] - 'a'

		// add right char
		if windowfreq[r] == s1freq[r] {
			match--
		}
		windowfreq[r]++
		if windowfreq[r] == s1freq[r] {
			match++
		}

		// remove left char
		if windowfreq[l] == s1freq[l] {
			match--
		}
		windowfreq[l]--
		if windowfreq[l] == s1freq[l] {
			match++
		}

		left++
		if match == 26 {
			return true
		}
	}
	return false
}
