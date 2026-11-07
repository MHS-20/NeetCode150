package backtracking

func partition(s string) [][]string {
	var result [][]string
	var path []string

	var backtrack func(start int)
	backtrack = func(start int) {
		if start == len(s) {
			result = append(result, append([]string(nil), path...))
			return
		}
		for i := start; i < len(s); i++ {
			if !isPalindrome(s, start, i) {
				continue
			}
			path = append(path, s[start:i+1])
			backtrack(i + 1)
			path = path[:len(path)-1]
		}
	}

	backtrack(0)
	return result
}

func isPalindrome(s string, l, r int) bool {
	for l < r {
		if s[l] != s[r] {
			return false
		}
		l, r = l+1, r-1
	}
	return true
}
