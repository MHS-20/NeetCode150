import java.util.HashMap;
import java.util.Map;

class Solution {
    public Node copyRandomList(Node head) {
        Map<Node, Node> copyOf = new HashMap<>();
        copyOf.put(null, null); // null original -> null copy

        // pass 1: create all copies (no links yet)
        for (Node cur = head; cur != null; cur = cur.next)
            copyOf.put(cur, new Node(cur.val));

        // pass 2: wire up next and random
        for (Node cur = head; cur != null; cur = cur.next) {
            copyOf.get(cur).next = copyOf.get(cur.next);
            copyOf.get(cur).random = copyOf.get(cur.random);
        }

        return copyOf.get(head);
    }
}
