from tree_node import TreeNode


class Solution:
    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        lo, hi = min(p.val, q.val), max(p.val, q.val)

        # the LCA is the first node whose value falls between p and q
        while root:
            if root.val < lo:
                root = root.right
            elif root.val > hi:
                root = root.left
            else:
                return root

        return None
