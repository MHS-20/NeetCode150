from typing import Optional

from tree_node import TreeNode


class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        best = 0

        def height(node: Optional[TreeNode]) -> int:
            nonlocal best
            if not node:
                return 0

            l = height(node.left)
            r = height(node.right)

            best = max(best, l + r)
            return 1 + max(l, r)

        height(root)
        return best
