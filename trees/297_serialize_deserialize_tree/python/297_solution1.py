from typing import Optional

from tree_node import TreeNode


class Codec:
    def serialize(self, root: Optional[TreeNode]) -> str:
        ser = []

        def dfs(node: Optional[TreeNode]) -> None:
            if not node:
                ser.append("N#")
                return
            ser.append(f"{node.val}#")
            dfs(node.left)
            dfs(node.right)

        dfs(root)
        return "".join(ser)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        tokens = iter(data.split("#"))

        def dfs() -> Optional[TreeNode]:
            tok = next(tokens)
            if tok == "N":
                return None

            node = TreeNode(int(tok))
            node.left = dfs()  # consumes the left subtree's tokens
            node.right = dfs()  # continues from there
            return node

        return dfs()
