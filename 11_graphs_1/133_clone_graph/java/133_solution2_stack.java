import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;

class Solution {
    public Node cloneGraph(Node node) {
        if (node == null)
            return null;

        Map<Node, Node> clones = new HashMap<>();
        Deque<Node> st = new ArrayDeque<>();
        clones.put(node, new Node(node.val));
        st.push(node);

        while (!st.isEmpty()) {
            Node cur = st.pop();
            for (Node neighbor : cur.neighbors) {
                if (!clones.containsKey(neighbor)) {
                    clones.put(neighbor, new Node(neighbor.val));
                    st.push(neighbor);
                }
                clones.get(cur).neighbors.add(clones.get(neighbor));
            }
        }
        return clones.get(node);
    }
}
