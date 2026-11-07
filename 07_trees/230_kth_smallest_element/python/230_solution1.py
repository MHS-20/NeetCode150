from typing import Optional

from tree_node import TreeNode


class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        idx, res = k, 0

        def dfs(node: Optional[TreeNode]) -> None:
            nonlocal idx, res
            if not node or idx == 0:
                return

            dfs(node.left)
            idx -= 1

            if idx == 0:
                res = node.val
                return

            dfs(node.right)

        dfs(root)
        return res
