package trees

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if p.Val > q.Val {
		return lowestCommonAncestor(root, q, p)
	}

	if root.Val >= p.Val && root.Val <= q.Val {
		return root
	}

	if q.Val < root.Val {
		return lowestCommonAncestor(root.Left, p, q)
	}
	return lowestCommonAncestor(root.Right, p, q)
}
