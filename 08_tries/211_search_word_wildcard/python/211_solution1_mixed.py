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
        return self._search_from(self.root, word, 0)

    def _search_from(self, cur: Node, word: str, pos: int) -> bool:
        for i in range(pos, len(word)):
            ch = word[i]
            if ch != ".":
                cur = cur.children.get(ch)
                if not cur:
                    return False
            else:
                return any(
                    self._search_from(n, word, i + 1) for n in cur.children.values()
                )
        return cur.is_end
