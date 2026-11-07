package trees

func maxDepth(root *TreeNode) int {
	return findDepth(root, 0)
}

func findDepth(root *TreeNode, count int) int {
	if root == nil {
		return count
	}
	return max(findDepth(root.Left, count+1), findDepth(root.Right, count+1))
}
