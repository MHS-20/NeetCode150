package tries

type node struct {
	children [26]*node
	word     string // non-empty means a word ends here
}

func (root *node) insert(word string) {
	cur := root
	for _, ch := range word {
		i := ch - 'a'
		if cur.children[i] == nil {
			cur.children[i] = &node{}
		}
		cur = cur.children[i]
	}
	cur.word = word
}

var dirs = [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

func dfs(board [][]byte, n *node, r, c int, res *[]string) {
	ch := board[r][c]
	next := n.children[ch-'a']
	if next == nil {
		return
	}

	if next.word != "" {
		*res = append(*res, next.word)
		next.word = "" // avoid duplicates
	}

	board[r][c] = '#' // mark visited
	for _, d := range dirs {
		nr, nc := r+d[0], c+d[1]
		if nr < 0 || nr >= len(board) || nc < 0 || nc >= len(board[0]) {
			continue
		}
		if board[nr][nc] == '#' {
			continue
		}
		dfs(board, next, nr, nc, res)
	}
	board[r][c] = ch // unmark
}

func findWords(board [][]byte, words []string) []string {
	root := &node{}
	for _, w := range words {
		root.insert(w)
	}

	res := []string{}
	for r := range board {
		for c := range board[0] {
			dfs(board, root, r, c, &res)
		}
	}
	return res
}
