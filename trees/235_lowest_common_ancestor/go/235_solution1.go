package trees

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	lo, hi := min(p.Val, q.Val), max(p.Val, q.Val)

	// the LCA is the first node whose value falls between p and q
	for root != nil {
		if root.Val < lo {
			root = root.Right
		} else if root.Val > hi {
			root = root.Left
		} else {
			return root
		}
	}

	return nil
}
