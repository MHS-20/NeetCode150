package trees

import "math"

func maxPathSum(root *TreeNode) int {
	mx := math.MinInt

	var dfs func(node *TreeNode) int
	dfs = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		l := max(0, dfs(node.Left))
		r := max(0, dfs(node.Right))

		mx = max(mx, l+r+node.Val)
		return max(l, r) + node.Val
	}

	dfs(root)
	return mx
}
