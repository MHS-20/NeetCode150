package greedy

func partitionLabels(s string) []int {
	var last [26]int
	for i := 0; i < len(s); i++ {
		last[s[i]-'a'] = i
	}

	result := []int{}
	start, end := 0, 0

	for i := 0; i < len(s); i++ {
		end = max(end, last[s[i]-'a'])
		if i == end {
			result = append(result, end-start+1)
			start = i + 1
		}
	}

	return result
}
