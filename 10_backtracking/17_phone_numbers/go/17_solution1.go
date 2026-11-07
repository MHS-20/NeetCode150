package backtracking

var mapping = [10]string{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}

func letterCombinations(digits string) []string {
	var result []string
	if len(digits) == 0 {
		return result
	}
	cur := make([]byte, 0, len(digits))

	var backtrack func(idx int)
	backtrack = func(idx int) {
		if idx == len(digits) {
			result = append(result, string(cur))
			return
		}
		for _, ch := range []byte(mapping[digits[idx]-'0']) {
			cur = append(cur, ch) // choose
			backtrack(idx + 1)
			cur = cur[:len(cur)-1] // un-choose
		}
	}

	backtrack(0)
	return result
}
