class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        int lo = Math.min(p.val, q.val);
        int hi = Math.max(p.val, q.val);

        // the LCA is the first node whose value falls between p and q
        while (root != null) {
            if (root.val < lo)
                root = root.right;
            else if (root.val > hi)
                root = root.left;
            else
                return root;
        }

        return null;
    }
}
