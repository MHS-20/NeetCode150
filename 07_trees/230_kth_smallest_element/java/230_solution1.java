class Solution {
    private int idx;
    private int res;

    public int kthSmallest(TreeNode root, int k) {
        idx = k;
        dfs(root);
        return res;
    }

    private void dfs(TreeNode node) {
        if (node == null || idx == 0)
            return;

        dfs(node.left);
        if (idx == 0)
            return; // answer found in the left subtree
        idx--;

        if (idx == 0) {
            res = node.val;
            return;
        }

        dfs(node.right);
    }
}
