package graphs

func canFinish(numCourses int, prerequisites [][]int) bool {
	adjacency := make([][]int, numCourses)
	for _, p := range prerequisites {
		adjacency[p[0]] = append(adjacency[p[0]], p[1])
	}

	state := make([]int, numCourses) // 0 = unvisited, 1 = on path, 2 = done

	var dfs func(node int) bool
	dfs = func(node int) bool {
		if state[node] == 1 {
			return false // back on the current path: cycle
		}
		if state[node] == 2 {
			return true // already fully explored
		}

		state[node] = 1
		for _, next := range adjacency[node] {
			if !dfs(next) {
				return false
			}
		}
		state[node] = 2
		return true
	}

	for i := 0; i < numCourses; i++ {
		if !dfs(i) {
			return false
		}
	}
	return true
}
