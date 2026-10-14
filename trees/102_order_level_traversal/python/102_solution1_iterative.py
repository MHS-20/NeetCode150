from collections import deque
from typing import List, Optional

from tree_node import TreeNode


class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        res = []
        if not root:
            return res

        q = deque([root])

        while q:
            cur = []

            for _ in range(len(q)):
                node = q.popleft()

                cur.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            res.append(cur)
        return res
