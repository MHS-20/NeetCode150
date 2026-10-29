package graphs

func cloneGraph(node *Node) *Node {
	clones := map[*Node]*Node{}

	var clone func(node *Node) *Node
	clone = func(node *Node) *Node {
		if node == nil {
			return nil
		}

		if _, ok := clones[node]; !ok {
			clones[node] = &Node{Val: node.Val}
			for _, cur := range node.Neighbors {
				clones[node].Neighbors = append(clones[node].Neighbors, clone(cur))
			}
		}

		return clones[node]
	}

	return clone(node)
}
