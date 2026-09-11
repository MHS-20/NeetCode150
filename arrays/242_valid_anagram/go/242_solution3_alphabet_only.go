// works if chars are a-z only
package solution

func isAnagram(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}

	var count [26]int
	for i := 0; i < len(s); i++ {
		count[s[i]-'a']++
		count[t[i]-'a']--
	}

	for _, c := range count {
		if c != 0 {
			return false
		}
	}

	return true
}
