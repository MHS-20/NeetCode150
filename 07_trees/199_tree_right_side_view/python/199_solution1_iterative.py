from collections import deque
from typing import List, Optional

from tree_node import TreeNode


class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        res = []
        if not root:
            return res

        q = deque([root])

        while q:
            sz = len(q)
            for i in range(sz):
                node = q.popleft()

                if i == sz - 1:
                    res.append(node.val)

                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return res
