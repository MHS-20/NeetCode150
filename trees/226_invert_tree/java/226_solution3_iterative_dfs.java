import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public TreeNode invertTree(TreeNode root) {
        Deque<TreeNode> st = new ArrayDeque<>();
        if (root != null)
            st.push(root);

        while (!st.isEmpty()) {
            TreeNode cur = st.pop();

            TreeNode tmp = cur.left;
            cur.left = cur.right;
            cur.right = tmp;

            if (cur.left != null)
                st.push(cur.left);
            if (cur.right != null)
                st.push(cur.right);
        }

        return root;
    }
}
