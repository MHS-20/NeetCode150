package trees

func isBalanced(root *TreeNode) bool {
	// returns the subtree height, or -1 as soon as any subtree is unbalanced
	var height func(node *TreeNode) int
	height = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		l := height(node.Left)
		if l == -1 {
			return -1
		}

		r := height(node.Right)
		if r == -1 {
			return -1
		}

		if l-r > 1 || r-l > 1 {
			return -1
		}

		return 1 + max(l, r)
	}

	return height(root) != -1
}
