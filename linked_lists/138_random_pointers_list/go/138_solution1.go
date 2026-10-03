package linkedlists

func copyRandomList(head *Node) *Node {
	copyOf := map[*Node]*Node{nil: nil} // nil original -> nil copy

	// pass 1: create all copies (no links yet)
	for cur := head; cur != nil; cur = cur.Next {
		copyOf[cur] = &Node{Val: cur.Val}
	}

	// pass 2: wire up next and random
	for cur := head; cur != nil; cur = cur.Next {
		copyOf[cur].Next = copyOf[cur.Next]
		copyOf[cur].Random = copyOf[cur.Random]
	}

	return copyOf[head]
}
