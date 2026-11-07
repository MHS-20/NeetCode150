package trees

import "math"

func goodNodes(root *TreeNode) int {
	count := 0

	var dfs func(node *TreeNode, maxSoFar int)
	dfs = func(node *TreeNode, maxSoFar int) {
		if node == nil {
			return
		}
		if node.Val >= maxSoFar {
			count++
			maxSoFar = node.Val
		}
		dfs(node.Left, maxSoFar)
		dfs(node.Right, maxSoFar)
	}

	dfs(root, math.MinInt)
	return count
}
