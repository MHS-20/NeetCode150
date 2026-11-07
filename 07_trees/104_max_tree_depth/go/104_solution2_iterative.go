package trees

func maxDepth(root *TreeNode) int {
	queue := []*TreeNode{}
	if root != nil {
		queue = append(queue, root)
	}

	depth := 0
	for len(queue) > 0 {
		size := len(queue)
		depth++

		for i := 0; i < size; i++ {
			cur := queue[i]

			if cur.Left != nil {
				queue = append(queue, cur.Left)
			}
			if cur.Right != nil {
				queue = append(queue, cur.Right)
			}
		}
		queue = queue[size:]
	}

	return depth
}
