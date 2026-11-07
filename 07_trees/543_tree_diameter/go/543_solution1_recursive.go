package trees

func diameterOfBinaryTree(root *TreeNode) int {
	best := 0

	var height func(node *TreeNode) int
	height = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		l := height(node.Left)
		r := height(node.Right)

		best = max(best, l+r)
		return 1 + max(l, r)
	}

	height(root)
	return best
}
