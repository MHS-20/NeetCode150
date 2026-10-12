from collections import deque
from typing import Optional

from tree_node import TreeNode


class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        q = deque([root] if root else [])

        depth = 0
        while q:
            depth += 1

            for _ in range(len(q)):
                cur = q.popleft()

                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)

        return depth
