from typing import Optional

from tree_node import TreeNode


class Solution:
    def goodNodes(self, root: Optional[TreeNode]) -> int:
        count = 0

        def dfs(node: Optional[TreeNode], max_so_far: int) -> None:
            nonlocal count
            if not node:
                return
            if node.val >= max_so_far:
                count += 1
                max_so_far = node.val
            dfs(node.left, max_so_far)
            dfs(node.right, max_so_far)

        dfs(root, float("-inf"))
        return count
