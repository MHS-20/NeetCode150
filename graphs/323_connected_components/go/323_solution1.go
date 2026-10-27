package graphs

func countComponents(n int, edges [][]int) int {
	parent := make([]int, n+1)
	count := n
	for i := 1; i <= n; i++ {
		parent[i] = i
	}

	for _, edge := range edges {
		ra := find(parent, edge[0])
		rb := find(parent, edge[1])
		if ra != rb {
			count--
		}
		parent[rb] = ra
	}
	return count
}

func find(parent []int, x int) int {
	for parent[x] != x {
		x = parent[x]
	}
	return x
}
