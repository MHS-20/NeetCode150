from typing import Dict, Optional

from node import Node


class Solution:
    def __init__(self) -> None:
        self.clones: Dict[Node, Node] = {}

    def cloneGraph(self, node: Optional[Node]) -> Optional[Node]:
        if not node:
            return None

        if node not in self.clones:
            self.clones[node] = Node(node.val)
            for cur in node.neighbors:
                self.clones[node].neighbors.append(self.cloneGraph(cur))

        return self.clones[node]
