from typing import List, Optional

from tree_node import TreeNode


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        in_index = {v: i for i, v in enumerate(inorder)}
        pre_idx = 0

        def build(in_lo: int, in_hi: int) -> Optional[TreeNode]:
            nonlocal pre_idx
            if in_lo > in_hi:
                return None

            root_val = preorder[pre_idx]
            pre_idx += 1
            mid = in_index[root_val]

            cur = TreeNode(root_val)
            cur.left = build(in_lo, mid - 1)
            cur.right = build(mid + 1, in_hi)
            return cur

        return build(0, len(inorder) - 1)
