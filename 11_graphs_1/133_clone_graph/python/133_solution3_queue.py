from collections import deque
from typing import Optional

from node import Node


class Solution:
    def cloneGraph(self, node: Optional[Node]) -> Optional[Node]:
        if not node:
            return None

        clones = {node: Node(node.val)}
        q = deque([node])

        while q:
            cur = q.popleft()
            for neighbor in cur.neighbors:
                if neighbor not in clones:
                    clones[neighbor] = Node(neighbor.val)
                    q.append(neighbor)
                clones[cur].neighbors.append(clones[neighbor])
        return clones[node]
