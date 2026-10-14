package trees

func levelOrder(root *TreeNode) [][]int {
	res := [][]int{}

	var dfs func(node *TreeNode, depth int)
	dfs = func(node *TreeNode, depth int) {
		if node == nil {
			return
		}

		// create slice for new depth
		if depth == len(res) {
			res = append(res, []int{})
		}

		res[depth] = append(res[depth], node.Val)

		dfs(node.Left, depth+1)
		dfs(node.Right, depth+1)
	}

	dfs(root, 0)
	return res
}
