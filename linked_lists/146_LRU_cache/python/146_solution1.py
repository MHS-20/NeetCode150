class Node:
    def __init__(self, key: int = 0, value: int = 0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None


class LRUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.map = {}
        self.head = Node()  # dummy nodes
        self.tail = Node()
        self.head.next = self.tail
        self.tail.prev = self.head

    def _remove(self, n: Node) -> None:
        n.prev.next = n.next
        n.next.prev = n.prev

    def _insert_front(self, n: Node) -> None:
        n.prev = self.head
        n.next = self.head.next
        self.head.next.prev = n
        self.head.next = n

    def get(self, key: int) -> int:
        n = self.map.get(key)
        if n is None:
            return -1

        self._remove(n)
        self._insert_front(n)
        return n.value

    def put(self, key: int, value: int) -> None:
        n = self.map.get(key)
        if n is not None:
            n.value = value
            self._remove(n)
            self._insert_front(n)
            return

        if len(self.map) == self.cap:
            lru = self.tail.prev
            self._remove(lru)
            del self.map[lru.key]

        n = Node(key, value)
        self.map[key] = n
        self._insert_front(n)
