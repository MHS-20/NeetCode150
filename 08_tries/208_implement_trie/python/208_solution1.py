from typing import Optional


class Node:
    def __init__(self):
        self.children: dict[str, "Node"] = {}
        self.is_end = False


class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word: str) -> None:
        cur = self.root
        for ch in word:
            cur = cur.children.setdefault(ch, Node())
        cur.is_end = True

    def search(self, word: str) -> bool:
        node = self._walk(word)
        return node is not None and node.is_end

    def startsWith(self, prefix: str) -> bool:
        return self._walk(prefix) is not None

    # returns the node reached by following s, or None if the path breaks
    def _walk(self, s: str) -> Optional[Node]:
        cur = self.root
        for ch in s:
            cur = cur.children.get(ch)
            if not cur:
                return None
        return cur
