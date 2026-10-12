from typing import Optional

from tree_node import TreeNode


class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        return self.findDepth(root, 0)

    def findDepth(self, root: Optional[TreeNode], count: int) -> int:
        if not root:
            return count
        return max(
            self.findDepth(root.left, count + 1),
            self.findDepth(root.right, count + 1),
        )
