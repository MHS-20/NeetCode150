package trees

func levelOrder(root *TreeNode) [][]int {
	res := [][]int{}
	if root == nil {
		return res
	}

	queue := []*TreeNode{root}

	for len(queue) > 0 {
		sz := len(queue)
		cur := make([]int, 0, sz)

		for _, node := range queue[:sz] {
			cur = append(cur, node.Val)
			if node.Left != nil {
				queue = append(queue, node.Left)
			}
			if node.Right != nil {
				queue = append(queue, node.Right)
			}
		}

		queue = queue[sz:]
		res = append(res, cur)
	}

	return res
}
