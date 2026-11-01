package greedy

// hi is the count if every * is a '('. If even that drops below 0, there's an
// unmatched ')' no matter what. lo is the count if every * is a ')'. Clamping
// it to 0 throws away choices that would close more than is open.
func checkValidString(s string) bool {
	lo, hi := 0, 0 // min and max possible number of open '('

	for i := 0; i < len(s); i++ {
		switch s[i] {
		case '(':
			lo++
			hi++
		case ')':
			lo--
			hi--
		default: // '*' could be ')' or '('
			lo--
			hi++
		}

		if hi < 0 {
			return false // too many ')', even with every '*' as '('
		}
		lo = max(lo, 0) // the count can't go negative, so drop those choices
	}

	return lo == 0 // some choice of '*' leaves zero open
}
