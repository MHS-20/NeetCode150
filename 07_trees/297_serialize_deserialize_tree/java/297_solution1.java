public class Codec {
    private int pos;

    public String serialize(TreeNode root) {
        StringBuilder ser = new StringBuilder();
        serDfs(root, ser);
        return ser.toString();
    }

    private void serDfs(TreeNode node, StringBuilder ser) {
        if (node == null) {
            ser.append("N#");
            return;
        }
        ser.append(node.val).append('#');
        serDfs(node.left, ser);
        serDfs(node.right, ser);
    }

    public TreeNode deserialize(String data) {
        pos = 0;
        return desDfs(data);
    }

    private TreeNode desDfs(String data) {
        int end = data.indexOf('#', pos); // next delimiter
        String tok = data.substring(pos, end);
        pos = end + 1; // move cursor past '#'

        if (tok.equals("N"))
            return null;

        TreeNode node = new TreeNode(Integer.parseInt(tok));
        node.left = desDfs(data);  // advances pos past the left subtree
        node.right = desDfs(data); // continues from there
        return node;
    }
}
