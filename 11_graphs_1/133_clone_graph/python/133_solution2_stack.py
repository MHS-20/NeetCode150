from typing import Optional

from node import Node


class Solution:
    def cloneGraph(self, node: Optional[Node]) -> Optional[Node]:
        if not node:
            return None

        clones = {node: Node(node.val)}
        st = [node]

        while st:
            cur = st.pop()
            for neighbor in cur.neighbors:
                if neighbor not in clones:
                    clones[neighbor] = Node(neighbor.val)
                    st.append(neighbor)
                clones[cur].neighbors.append(clones[neighbor])
        return clones[node]
