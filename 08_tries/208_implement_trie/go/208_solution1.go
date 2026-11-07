package tries

type Trie struct {
	children [26]*Trie
	isEnd    bool
}

func Constructor() Trie {
	return Trie{}
}

func (t *Trie) Insert(word string) {
	cur := t
	for _, ch := range word {
		i := ch - 'a'
		if cur.children[i] == nil {
			cur.children[i] = &Trie{}
		}
		cur = cur.children[i]
	}
	cur.isEnd = true
}

// walk returns the node reached by following s, or nil if the path breaks.
func (t *Trie) walk(s string) *Trie {
	cur := t
	for _, ch := range s {
		cur = cur.children[ch-'a']
		if cur == nil {
			return nil
		}
	}
	return cur
}

func (t *Trie) Search(word string) bool {
	node := t.walk(word)
	return node != nil && node.isEnd
}

func (t *Trie) StartsWith(prefix string) bool {
	return t.walk(prefix) != nil
}
