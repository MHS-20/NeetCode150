import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int goodNodes(TreeNode root) {
        int count = 0;
        Deque<TreeNode> nodes = new ArrayDeque<>();
        Deque<Integer> maxes = new ArrayDeque<>();
        nodes.push(root);
        maxes.push(Integer.MIN_VALUE);

        while (!nodes.isEmpty()) {
            TreeNode node = nodes.pop();
            int maxSoFar = maxes.pop();

            if (node.val >= maxSoFar) {
                count++;
                maxSoFar = node.val;
            }

            if (node.left != null) {
                nodes.push(node.left);
                maxes.push(maxSoFar);
            }
            if (node.right != null) {
                nodes.push(node.right);
                maxes.push(maxSoFar);
            }
        }
        return count;
    }
}
