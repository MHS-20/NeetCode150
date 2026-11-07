import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;

        // 1. store every node
        Deque<ListNode> deque = new ArrayDeque<>();
        for (ListNode curr = head; curr != null; curr = curr.next)
            deque.addLast(curr);

        // 2. relink alternating between the front and the back
        ListNode tail = deque.pollFirst(); // the head stays first
        while (!deque.isEmpty()) {
            tail.next = deque.pollLast();
            tail = tail.next;
            if (!deque.isEmpty()) {
                tail.next = deque.pollFirst();
                tail = tail.next;
            }
        }
        tail.next = null;
    }
}
