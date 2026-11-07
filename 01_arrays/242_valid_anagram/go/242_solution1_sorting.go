package solution

import "sort"

func isAnagram(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}

	sRunes := []rune(s)
	tRunes := []rune(t)
	sort.Slice(sRunes, func(i, j int) bool { return sRunes[i] < sRunes[j] })
	sort.Slice(tRunes, func(i, j int) bool { return tRunes[i] < tRunes[j] })

	return string(sRunes) == string(tRunes)
}
