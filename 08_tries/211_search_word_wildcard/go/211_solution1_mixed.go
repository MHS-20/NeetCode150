package tries

type WordDictionary struct {
	children [26]*WordDictionary
	isEnd    bool
}

func Constructor() WordDictionary {
	return WordDictionary{}
}

func (d *WordDictionary) AddWord(word string) {
	cur := d
	for _, ch := range word {
		i := ch - 'a'
		if cur.children[i] == nil {
			cur.children[i] = &WordDictionary{}
		}
		cur = cur.children[i]
	}
	cur.isEnd = true
}

func (d *WordDictionary) Search(word string) bool {
	return d.searchFrom(word, 0)
}

func (d *WordDictionary) searchFrom(word string, pos int) bool {
	cur := d
	for i := pos; i < len(word); i++ {
		if word[i] != '.' {
			cur = cur.children[word[i]-'a']
			if cur == nil {
				return false
			}
			continue
		}
		for _, n := range cur.children {
			if n != nil && n.searchFrom(word, i+1) {
				return true
			}
		}
		return false
	}
	return cur.isEnd
}
