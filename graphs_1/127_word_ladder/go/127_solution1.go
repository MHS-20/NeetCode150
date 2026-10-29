package graphs

func ladderLength(beginWord string, endWord string, wordList []string) int {
	words := make(map[string]bool, len(wordList))
	for _, w := range wordList {
		words[w] = true
	}
	if !words[endWord] {
		return 0
	}

	q := []string{beginWord}
	delete(words, beginWord)
	length := 1

	for len(q) > 0 {
		sz := len(q)
		for i := 0; i < sz; i++ {
			w := []byte(q[0])
			q = q[1:]

			for pos := range w {
				original := w[pos]
				for c := byte('a'); c <= 'z'; c++ {
					if c == original {
						continue
					}
					w[pos] = c
					s := string(w)
					if s == endWord {
						return length + 1
					}
					if words[s] {
						delete(words, s)
						q = append(q, s)
					}
				}
				w[pos] = original
			}
		}
		length++
	}
	return 0
}
