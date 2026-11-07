package trees

import "math"

type frame struct {
	node     *TreeNode
	maxSoFar int
}

func goodNodes(root *TreeNode) int {
	count := 0
	stack := []frame{{root, math.MinInt}}

	for len(stack) > 0 {
		f := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		if f.node == nil {
			continue
		}

		if f.node.Val >= f.maxSoFar {
			count++
			f.maxSoFar = f.node.Val
		}

		stack = append(stack, frame{f.node.Left, f.maxSoFar}, frame{f.node.Right, f.maxSoFar})
	}
	return count
}
