from typing import Optional

from tree_node import TreeNode


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        stack = [root] if root else []

        while stack:
            cur = stack.pop()

            cur.left, cur.right = cur.right, cur.left

            if cur.left:
                stack.append(cur.left)
            if cur.right:
                stack.append(cur.right)

        return root
