class Solution {
    public boolean isValidBST(TreeNode root) {
        return dfs(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }

    private boolean dfs(TreeNode node, long lowerbound, long upperbound) {
        if (node == null)
            return true;

        if (node.val <= lowerbound || node.val >= upperbound)
            return false;

        return dfs(node.right, node.val, upperbound) &&
               dfs(node.left, lowerbound, node.val);
    }
}
