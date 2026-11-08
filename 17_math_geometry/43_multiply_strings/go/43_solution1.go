package mathgeometry

func multiply(num1 string, num2 string) string {
	n, m := len(num1), len(num2)
	pos := make([]int, n+m)

	for i := n - 1; i >= 0; i-- {
		for j := m - 1; j >= 0; j-- {
			mul := int(num1[i]-'0') * int(num2[j]-'0')
			sum := mul + pos[i+j+1]
			pos[i+j+1] = sum % 10 // ones digit stays here
			pos[i+j] += sum / 10  // carry goes one position left
		}
	}

	res := make([]byte, 0, n+m)
	for _, d := range pos {
		if !(len(res) == 0 && d == 0) { // skip leading zeros
			res = append(res, byte('0'+d))
		}
	}
	if len(res) == 0 {
		return "0"
	}
	return string(res)
}
