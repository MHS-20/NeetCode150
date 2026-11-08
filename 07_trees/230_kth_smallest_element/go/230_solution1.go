package trees

func kthSmallest(root *TreeNode, k int) int {
	res := 0

	var dfs func(node *TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil || k == 0 {
			return
		}

		dfs(node.Left)
		if k == 0 {
			return // answer found in the left subtree
		}
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
