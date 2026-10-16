from typing import Optional

from tree_node import TreeNode


class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(node: Optional[TreeNode], lowerbound: float, upperbound: float) -> bool:
            if not node:
                return True
            if node.val <= lowerbound or node.val >= upperbound:
                return False
            return dfs(node.right, node.val, upperbound) and dfs(
                node.left, lowerbound, node.val
            )

        return dfs(root, float("-inf"), float("inf"))
