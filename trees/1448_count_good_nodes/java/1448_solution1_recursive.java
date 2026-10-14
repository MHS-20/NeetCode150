class Solution {
    private int count;

    public int goodNodes(TreeNode root) {
        count = 0;
        dfs(root, Integer.MIN_VALUE);
        return count;
    }

    private void dfs(TreeNode node, int maxSoFar) {
        if (node == null)
            return;
        if (node.val >= maxSoFar) {
            count++;
            maxSoFar = node.val;
        }
        dfs(node.left, maxSoFar);
        dfs(node.right, maxSoFar);
    }
}
