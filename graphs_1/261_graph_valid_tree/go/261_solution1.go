package graphs

func validTree(n int, edges [][]int) bool {
	count := n
	parent := make([]int, n+1)
	for i := 1; i <= n; i++ {
		parent[i] = i
	}

	for _, edge := range edges {
		ra := find(parent, edge[0])
		rb := find(parent, edge[1])
		if ra == rb {
			return false
		}
		count--
		parent[rb] = ra
	}
	return count == 1
}

func find(parent []int, x int) int {
	for parent[x] != x {
		x = parent[x]
	}
	return x
}
