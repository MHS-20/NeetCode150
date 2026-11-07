import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;

        // 1. find the end of the first half
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // 2. cut the list and push the second half onto a stack
        Deque<ListNode> stack = new ArrayDeque<>();
        for (ListNode curr = slow.next; curr != null; curr = curr.next)
            stack.push(curr);
        slow.next = null; // split into two lists

        // 3. merge: popping the stack yields the second half in reverse
        ListNode first = head;
        while (!stack.isEmpty()) {
            ListNode second = stack.pop();
            second.next = first.next;
            first.next = second;
            first = second.next;
        }
    }
}
