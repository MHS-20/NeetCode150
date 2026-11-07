package main

func generateParenthesis(n int) []string {
	res := []string{}
	cur := make([]byte, 0, 2*n)

	var backtrack func(opened, closed int)
	backtrack = func(opened, closed int) {
		if closed == n { // implies opened == n too
			res = append(res, string(cur)) // copies once, only for finished answers
			return
		}

		if opened < n {
			cur = append(cur, '(')      // choose
			backtrack(opened+1, closed) // explore
			cur = cur[:len(cur)-1]      // undo
		}

		if closed < opened {
			cur = append(cur, ')')
			backtrack(opened, closed+1)
			cur = cur[:len(cur)-1]
		}
	}

	backtrack(0, 0)
	return res
}
