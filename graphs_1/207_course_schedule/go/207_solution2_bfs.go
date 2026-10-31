package graphs

func canFinish(numCourses int, prerequisites [][]int) bool {
	unlocks := make([][]int, numCourses) // b -> courses that need b
	remaining := make([]int, numCourses) // prerequisites still missing

	for _, p := range prerequisites {
		a, b := p[0], p[1]
		unlocks[b] = append(unlocks[b], a)
		remaining[a]++
	}

	queue := []int{}
	for c := 0; c < numCourses; c++ {
		if remaining[c] == 0 {
			queue = append(queue, c)
		}
	}

	taken := 0
	for len(queue) > 0 {
		c := queue[0]
		queue = queue[1:]
		taken++

		for _, next := range unlocks[c] {
			remaining[next]--
			if remaining[next] == 0 {
				queue = append(queue, next)
			}
		}
	}

	return taken == numCourses
}
