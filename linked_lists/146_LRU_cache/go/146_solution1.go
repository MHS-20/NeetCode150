package linkedlists

type lruNode struct {
	key, value int
	prev, next *lruNode
}

type LRUCache struct {
	cap        int
	head, tail *lruNode // dummy nodes
	nodes      map[int]*lruNode
}

func Constructor(capacity int) LRUCache {
	head, tail := &lruNode{}, &lruNode{}
	head.next = tail
	tail.prev = head
	return LRUCache{cap: capacity, head: head, tail: tail, nodes: map[int]*lruNode{}}
}

func (c *LRUCache) remove(n *lruNode) {
	n.prev.next = n.next
	n.next.prev = n.prev
}

func (c *LRUCache) insertFront(n *lruNode) {
	n.prev = c.head
	n.next = c.head.next
	c.head.next.prev = n
	c.head.next = n
}

func (c *LRUCache) Get(key int) int {
	n, ok := c.nodes[key]
	if !ok {
		return -1
	}

	c.remove(n)
	c.insertFront(n)
	return n.value
}

func (c *LRUCache) Put(key int, value int) {
	if n, ok := c.nodes[key]; ok {
		n.value = value
		c.remove(n)
		c.insertFront(n)
		return
	}

	if len(c.nodes) == c.cap {
		lru := c.tail.prev
		c.remove(lru)
		delete(c.nodes, lru.key)
	}

	n := &lruNode{key: key, value: value}
	c.nodes[key] = n
	c.insertFront(n)
}
