import java.util.HashMap;
import java.util.Map;

class Solution {
    private final Map<Node, Node> clones = new HashMap<>();

    public Node cloneGraph(Node node) {
        if (node == null)
            return null;

        if (!clones.containsKey(node)) {
            clones.put(node, new Node(node.val));
            for (Node cur : node.neighbors) {
                clones.get(node).neighbors.add(cloneGraph(cur));
            }
        }

        return clones.get(node);
    }
}
