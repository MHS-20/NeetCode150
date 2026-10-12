package trees

func invertTree(root *TreeNode) *TreeNode {
	stack := []*TreeNode{}
	if root != nil {
		stack = append(stack, root)
	}

	for len(stack) > 0 {
		cur := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		cur.Left, cur.Right = cur.Right, cur.Left

		if cur.Left != nil {
			stack = append(stack, cur.Left)
		}
		if cur.Right != nil {
			stack = append(stack, cur.Right)
		}
	}

	return root
}
