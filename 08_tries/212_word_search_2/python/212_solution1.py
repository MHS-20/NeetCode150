from typing import List, Optional


class Node:
    def __init__(self):
        self.children: dict[str, "Node"] = {}
        self.word: Optional[str] = None  # set means a word ends here


DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        root = Node()
        for w in words:
            cur = root
            for ch in w:
                cur = cur.children.setdefault(ch, Node())
            cur.word = w

        rows, cols = len(board), len(board[0])
        res = []

        def dfs(node: Node, r: int, c: int) -> None:
            ch = board[r][c]
            nxt = node.children.get(ch)
            if not nxt:
                return

            if nxt.word:
                res.append(nxt.word)
                nxt.word = None  # avoid duplicates

            board[r][c] = "#"  # mark visited
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and board[nr][nc] != "#":
                    dfs(nxt, nr, nc)
            board[r][c] = ch  # unmark

        for r in range(rows):
            for c in range(cols):
                dfs(root, r, c)
        return res
