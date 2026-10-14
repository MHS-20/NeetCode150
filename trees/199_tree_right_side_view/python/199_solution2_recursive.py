from typing import List, Optional

from tree_node import TreeNode


class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        res = []

        # visit right first, so the first node seen at each depth is the rightmost
        def dfs(node: Optional[TreeNode], depth: int) -> None:
            if not node:
                return

            if depth == len(res):
                res.append(node.val)

            dfs(node.right, depth + 1)
            dfs(node.left, depth + 1)

        dfs(root, 0)
        return res
