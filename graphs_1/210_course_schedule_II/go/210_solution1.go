package graphs

func findOrder(numCourses int, prerequisites [][]int) []int {
	adjacency := make([][]int, numCourses)
	for _, p := range prerequisites {
		adjacency[p[0]] = append(adjacency[p[0]], p[1])
	}

	state := make([]int, numCourses) // 0 = unvisited, 1 = on path, 2 = done
	order := make([]int, 0, numCourses)

	var dfs func(node int) bool
	dfs = func(node int) bool {
		if state[node] == 1 {
			return false // cycle
		}
		if state[node] == 2 {
			return true
		}

		state[node] = 1
		for _, next := range adjacency[node] {
			if !dfs(next) {
				return false
			}
		}
		state[node] = 2
		order = append(order, node)
		return true
	}

	for i := 0; i < numCourses; i++ {
		if !dfs(i) {
			return []int{}
		}
	}
	return order
}
