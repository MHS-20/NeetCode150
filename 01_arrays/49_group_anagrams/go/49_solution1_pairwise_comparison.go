package main

func groupAnagrams(strs []string) [][]string {
	result := [][]string{}

	for _, s := range strs {
		placed := false
		for i, group := range result {
			if isAnagram(s, group[0]) {
				result[i] = append(group, s)
				placed = true
				break
			}
		}

		if !placed {
			result = append(result, []string{s})
		}
	}

	return result
}

func isAnagram(s, t string) bool {
	if len(s) != len(t) {
		return false
	}

	freq := make(map[rune]int)
	for _, c := range s {
		freq[c]++
	}
	for _, c := range t {
		freq[c]--
		if freq[c] < 0 {
			return false
		}
	}
	return true
}
