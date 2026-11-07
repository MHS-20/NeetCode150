package trees

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if p.Val > q.Val {
		return lowestCommonAncestor(root, q, p)
	}

	for root != nil {
		if root.Val >= p.Val && root.Val <= q.Val {
			return root
		}

		if root.Val < p.Val {
			root = root.Right
		} else {
			root = root.Left
		}
	}

	return root
}
