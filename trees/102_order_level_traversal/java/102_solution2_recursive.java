import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        dfs(root, 0, res);
        return res;
    }

    private void dfs(TreeNode node, int depth, List<List<Integer>> res) {
        if (node == null)
            return;

        // create list for new depth
        if (depth == res.size())
            res.add(new ArrayList<>());

        res.get(depth).add(node.val);

        dfs(node.left, depth + 1, res);
        dfs(node.right, depth + 1, res);
    }
}
