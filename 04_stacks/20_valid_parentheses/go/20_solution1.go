package main

func isValid(s string) bool {
	expected := []byte{} // closing brackets we still owe

	for i := 0; i < len(s); i++ {
		switch c := s[i]; c {
		case '(':
			expected = append(expected, ')')
		case '[':
			expected = append(expected, ']')
		case '{':
			expected = append(expected, '}')
		default:
			n := len(expected)
			if n == 0 || expected[n-1] != c {
				return false
			}
			expected = expected[:n-1]
		}
	}
	return len(expected) == 0
}
