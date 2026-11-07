package graphs

func cloneGraph(node *Node) *Node {
	if node == nil {
		return nil
	}

	clones := map[*Node]*Node{node: {Val: node.Val}}
	st := []*Node{node}

	for len(st) > 0 {
		cur := st[len(st)-1]
		st = st[:len(st)-1]
		for _, neighbor := range cur.Neighbors {
			if _, ok := clones[neighbor]; !ok {
				clones[neighbor] = &Node{Val: neighbor.Val}
				st = append(st, neighbor)
			}
			clones[cur].Neighbors = append(clones[cur].Neighbors, clones[neighbor])
		}
	}
	return clones[node]
}
