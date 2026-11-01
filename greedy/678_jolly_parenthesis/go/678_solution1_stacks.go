package greedy

func checkValidString(s string) bool {
	var open, star []int // indices of unmatched '(' and '*'

	for i := 0; i < len(s); i++ {
		switch s[i] {
		case '(':
			open = append(open, i)
		case '*':
			star = append(star, i)
		case ')':
			if len(open) > 0 {
				open = open[:len(open)-1]
			} else if len(star) > 0 {
				star = star[:len(star)-1]
			} else {
				return false
			}
		}
	}

	// each leftover '(' needs a later '*' to close it
	for len(open) > 0 {
		if len(star) == 0 || star[len(star)-1] < open[len(open)-1] {
			return false
		}
		open = open[:len(open)-1]
		star = star[:len(star)-1]
	}
	return true
}
