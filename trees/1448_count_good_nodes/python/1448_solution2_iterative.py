from typing import Optional

from tree_node import TreeNode


class Solution:
    def goodNodes(self, root: Optional[TreeNode]) -> int:
        count = 0
        stack = [(root, float("-inf"))]

        while stack:
            node, max_so_far = stack.pop()
            if not node:
                continue

            if node.val >= max_so_far:
                count += 1
                max_so_far = node.val

            stack.append((node.left, max_so_far))
            stack.append((node.right, max_so_far))
        return count
