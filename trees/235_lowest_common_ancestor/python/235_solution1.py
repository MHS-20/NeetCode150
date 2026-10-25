from tree_node import TreeNode


class Solution:
    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        if p.val > q.val:
            return self.lowestCommonAncestor(root, q, p)

        while root:
            if p.val <= root.val <= q.val:
                return root

            if root.val < p.val:
                root = root.right
            else:
                root = root.left

        return root
