package solution

import "unicode/utf8"

func isAnagram(s string, t string) bool {
	// Explicit rune-count based length check; the map below (like solution2)
	// already iterates by rune, so Go needs no extra step for full unicode
	// safety beyond what range already gives.
	if utf8.RuneCountInString(s) != utf8.RuneCountInString(t) {
		return false
	}

	counts := make(map[rune]int)
	for _, c := range s {
		counts[c]++
	}

	for _, c := range t {
		counts[c]--
		if counts[c] < 0 {
			return false
		}
	}

	return true
}
