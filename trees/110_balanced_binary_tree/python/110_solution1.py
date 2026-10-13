from typing import Optional

from tree_node import TreeNode


class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        # returns the subtree height, or -1 as soon as any subtree is unbalanced
        def height(node: Optional[TreeNode]) -> int:
            if not node:
                return 0

            l = height(node.left)
            if l == -1:
                return -1

            r = height(node.right)
            if r == -1:
                return -1

            if abs(l - r) > 1:
                return -1

            return 1 + max(l, r)

        return height(root) != -1
