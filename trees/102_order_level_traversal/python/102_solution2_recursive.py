from typing import List, Optional

from tree_node import TreeNode


class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        res = []

        def dfs(node: Optional[TreeNode], depth: int) -> None:
            if not node:
                return

            # create list for new depth
            if depth == len(res):
                res.append([])

            res[depth].append(node.val)

            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)

        dfs(root, 0)
        return res
