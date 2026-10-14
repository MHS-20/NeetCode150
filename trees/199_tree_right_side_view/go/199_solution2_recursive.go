package trees

func rightSideView(root *TreeNode) []int {
	res := []int{}

	// visit right first, so the first node seen at each depth is the rightmost
	var dfs func(node *TreeNode, depth int)
	dfs = func(node *TreeNode, depth int) {
		if node == nil {
			return
		}

		if depth == len(res) {
			res = append(res, node.Val)
		}

		dfs(node.Right, depth+1)
		dfs(node.Left, depth+1)
	}

	dfs(root, 0)
	return res
}
