from typing import Optional

from tree_node import TreeNode


class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        mx = float("-inf")

        def dfs(node: Optional[TreeNode]) -> int:
            nonlocal mx
            if not node:
                return 0

            l = max(0, dfs(node.left))
            r = max(0, dfs(node.right))

            mx = max(mx, l + r + node.val)
            return max(l, r) + node.val

        dfs(root)
        return mx
