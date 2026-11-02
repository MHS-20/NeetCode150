package graphs

func foreignDictionary(words []string) string {
	var seen [26]bool
	var edge [26][26]bool
	var state [26]int // 0 = unvisited, 1 = visiting, 2 = done
	result := []byte{}

	// Returns false if a cycle is found
	var dfs func(u int) bool
	dfs = func(u int) bool {
		state[u] = 1
		for v := 0; v < 26; v++ {
			if !edge[u][v] {
				continue
			}
			if state[v] == 1 {
				return false // back edge: cycle
			}
			if state[v] == 0 && !dfs(v) {
				return false // propagate failure
			}
		}
		state[u] = 2
		result = append(result, byte('a'+u)) // post-order
		return true
	}

	// 1. Register every letter
	for _, w := range words {
		for i := 0; i < len(w); i++ {
			seen[w[i]-'a'] = true
		}
	}

	// 2. Build edges (no in-degree needed)
	for i := 0; i+1 < len(words); i++ {
		a, b := words[i], words[i+1]
		n := min(len(a), len(b))
		j := 0
		for j < n && a[j] == b[j] {
			j++
		}

		if j == n {
			if len(a) > len(b) {
				return ""
			}
			continue
		}
		edge[a[j]-'a'][b[j]-'a'] = true // duplicates are harmless here
	}

	// 3. DFS from every unvisited letter
	for c := 0; c < 26; c++ {
		if seen[c] && state[c] == 0 && !dfs(c) {
			return ""
		}
	}

	// 4. Post-order is reversed topological order
	for i, j := 0, len(result)-1; i < j; i, j = i+1, j-1 {
		result[i], result[j] = result[j], result[i]
	}
	return string(result)
}
