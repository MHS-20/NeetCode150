package graphs

func cloneGraph(node *Node) *Node {
	if node == nil {
		return nil
	}

	clones := map[*Node]*Node{node: {Val: node.Val}}
	q := []*Node{node}

	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		for _, neighbor := range cur.Neighbors {
			if _, ok := clones[neighbor]; !ok {
				clones[neighbor] = &Node{Val: neighbor.Val}
				q = append(q, neighbor)
			}
			clones[cur].Neighbors = append(clones[cur].Neighbors, clones[neighbor])
		}
	}
	return clones[node]
}
