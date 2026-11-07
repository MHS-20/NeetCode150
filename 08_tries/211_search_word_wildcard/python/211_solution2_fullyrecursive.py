from typing import Optional


class Node:
    def __init__(self):
        self.children: dict[str, "Node"] = {}
        self.is_end = False


class WordDictionary:
    def __init__(self):
        self.root = Node()

    def addWord(self, word: str) -> None:
        cur = self.root
        for ch in word:
            cur = cur.children.setdefault(ch, Node())
        cur.is_end = True

    def search(self, word: str) -> bool:
        return self._dfs(self.root, word, 0)

    def _dfs(self, cur: Optional[Node], word: str, i: int) -> bool:
        if not cur:
            return False
        if i == len(word):
            return cur.is_end

        if word[i] != ".":
            return self._dfs(cur.children.get(word[i]), word, i + 1)

        return any(self._dfs(child, word, i + 1) for child in cur.children.values())
