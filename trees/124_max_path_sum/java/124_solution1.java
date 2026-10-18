class Solution {
    private int mx;

    public int maxPathSum(TreeNode root) {
        mx = Integer.MIN_VALUE;
        dfs(root);
        return mx;
    }

    private int dfs(TreeNode node) {
        if (node == null)
            return 0;

        int l = Math.max(0, dfs(node.left));
        int r = Math.max(0, dfs(node.right));

        mx = Math.max(mx, l + r + node.val);
        return Math.max(l, r) + node.val;
    }
}
