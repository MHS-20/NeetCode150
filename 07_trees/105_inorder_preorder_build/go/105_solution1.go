package trees

func buildTree(preorder []int, inorder []int) *TreeNode {
	inIndex := make(map[int]int, len(inorder))
	for i, v := range inorder {
		inIndex[v] = i
	}

	preIdx := 0
	var build func(inLo, inHi int) *TreeNode
	build = func(inLo, inHi int) *TreeNode {
		if inLo > inHi {
			return nil
		}

		rootVal := preorder[preIdx]
		preIdx++
		mid := inIndex[rootVal]

		cur := &TreeNode{Val: rootVal}
		cur.Left = build(inLo, mid-1)
		cur.Right = build(mid+1, inHi)
		return cur
	}

	return build(0, len(inorder)-1)
}
