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
		next := &cur.children[ch-'a']
		if *next == nil {
			*next = &WordDictionary{}
		}
		cur = *next
	}
	cur.isEnd = true
}

func (d *WordDictionary) Search(word string) bool {
	return dfs(d, word, 0)
}

func dfs(cur *WordDictionary, word string, i int) bool {
	if cur == nil {
		return false
	}
	if i == len(word) {
		return cur.isEnd
	}

	if word[i] != '.' {
		return dfs(cur.children[word[i]-'a'], word, i+1)
	}

	for _, child := range cur.children {
		if dfs(child, word, i+1) {
			return true
		}
	}
	return false
}
