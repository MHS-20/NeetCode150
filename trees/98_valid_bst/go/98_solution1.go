package trees

import "math"

func isValidBST(root *TreeNode) bool {
	var dfs func(node *TreeNode, lowerbound, upperbound int) bool
	dfs = func(node *TreeNode, lowerbound, upperbound int) bool {
		if node == nil {
			return true
		}
		if node.Val <= lowerbound || node.Val >= upperbound {
			return false
		}
		return dfs(node.Right, node.Val, upperbound) &&
			dfs(node.Left, lowerbound, node.Val)
	}

	return dfs(root, math.MinInt, math.MaxInt)
}
