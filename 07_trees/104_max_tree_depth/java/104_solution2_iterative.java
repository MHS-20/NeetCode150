import java.util.ArrayDeque;
import java.util.Queue;

class Solution {
    public int maxDepth(TreeNode root) {
        Queue<TreeNode> q = new ArrayDeque<>();
        if (root != null)
            q.add(root);

        int depth = 0;
        while (!q.isEmpty()) {
            int size = q.size();
            depth++;

            for (int i = 0; i < size; i++) {
                TreeNode cur = q.poll();

                if (cur.left != null)
                    q.add(cur.left);
                if (cur.right != null)
                    q.add(cur.right);
            }
        }

        return depth;
    }
}
