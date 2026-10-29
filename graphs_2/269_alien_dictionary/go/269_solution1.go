package graphs

func foreignDictionary(words []string) string {
	var seen [26]bool
	var edge [26][26]bool
	var indeg [26]int
	total := 0

	for _, w := range words {
		for i := 0; i < len(w); i++ {
			if !seen[w[i]-'a'] {
				seen[w[i]-'a'] = true
				total++
			}
		}
	}

	for i := 0; i+1 < len(words); i++ {
		a, b := words[i], words[i+1]
		n := min(len(a), len(b))
		j := 0
		for j < n && a[j] == b[j] {
			j++
		}

		if j == n {
			if len(a) > len(b) {
				return "" // b is a proper prefix of a: invalid
			}
			continue
		}
		u, v := a[j]-'a', b[j]-'a'
		if !edge[u][v] { // avoid double-counting
			edge[u][v] = true
			indeg[v]++
		}
	}

	// Kahn's algorithm
	q := []int{}
	for c := 0; c < 26; c++ {
		if seen[c] && indeg[c] == 0 {
			q = append(q, c)
		}
	}

	result := []byte{}
	for len(q) > 0 {
		u := q[0]
		q = q[1:]
		result = append(result, byte('a'+u))
		for v := 0; v < 26; v++ {
			if edge[u][v] {
				indeg[v]--
				if indeg[v] == 0 {
					q = append(q, v)
				}
			}
		}
	}

	if len(result) != total {
		return ""
	}
	return string(result)
}
