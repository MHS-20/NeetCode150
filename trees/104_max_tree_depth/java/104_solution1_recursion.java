class Solution {
    public int maxDepth(TreeNode root) {
        return findDepth(root, 0);
    }

    private int findDepth(TreeNode root, int count) {
        if (root == null)
            return count;
        return Math.max(findDepth(root.left, count + 1), findDepth(root.right, count + 1));
    }
}
