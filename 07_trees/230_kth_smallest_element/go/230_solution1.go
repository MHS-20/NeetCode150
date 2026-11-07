package trees

func kthSmallest(root *TreeNode, k int) int {
	res := 0

	var dfs func(node *TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil || k == 0 {
			return
		}

		dfs(node.Left)
		k--

		if k == 0 {
			res = node.Val
			return
		}

		dfs(node.Right)
	}

	dfs(root)
	return res
}
