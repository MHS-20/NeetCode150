from collections import deque
from typing import Optional

from tree_node import TreeNode


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None

        q = deque([root])

        while q:
            cur = q.popleft()

            cur.left, cur.right = cur.right, cur.left

            if cur.left:
                q.append(cur.left)
            if cur.right:
                q.append(cur.right)

        return root
