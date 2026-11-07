package main

func generateParenthesis(n int) []string {
	res := []string{}

	var build func(opened, closed int, cur string)
	build = func(opened, closed int, cur string) {
		if closed == n { // implies opened == n too
			res = append(res, cur)
			return
		}
		if opened < n {
			build(opened+1, closed, cur+"(")
		}
		if closed < opened {
			build(opened, closed+1, cur+")")
		}
	}

	build(0, 0, "")
	return res
}
