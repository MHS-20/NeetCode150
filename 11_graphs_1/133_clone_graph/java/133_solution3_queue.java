import java.util.ArrayDeque;
import java.util.Queue;
import java.util.HashMap;
import java.util.Map;

class Solution {
    public Node cloneGraph(Node node) {
        if (node == null)
            return null;

        Map<Node, Node> clones = new HashMap<>();
        Queue<Node> q = new ArrayDeque<>();
        clones.put(node, new Node(node.val));
        q.offer(node);

        while (!q.isEmpty()) {
            Node cur = q.poll();
            for (Node neighbor : cur.neighbors) {
                if (!clones.containsKey(neighbor)) {
                    clones.put(neighbor, new Node(neighbor.val));
                    q.offer(neighbor);
                }
                clones.get(cur).neighbors.add(clones.get(neighbor));
            }
        }
        return clones.get(node);
    }
}
