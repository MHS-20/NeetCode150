package trees

import (
	"strconv"
	"strings"
)

type Codec struct{}

func Constructor() Codec {
	return Codec{}
}

func (c *Codec) serialize(root *TreeNode) string {
	var sb strings.Builder

	var dfs func(node *TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil {
			sb.WriteString("N#")
			return
		}
		sb.WriteString(strconv.Itoa(node.Val) + "#")
		dfs(node.Left)
		dfs(node.Right)
	}

	dfs(root)
	return sb.String()
}

func (c *Codec) deserialize(data string) *TreeNode {
	tokens := strings.Split(data, "#")
	pos := 0

	var dfs func() *TreeNode
	dfs = func() *TreeNode {
		tok := tokens[pos]
		pos++

		if tok == "N" {
			return nil
		}

		val, _ := strconv.Atoi(tok)
		node := &TreeNode{Val: val}
		node.Left = dfs()  // advances pos past the left subtree
		node.Right = dfs() // continues from there
		return node
	}

	return dfs()
}
