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

        // 2. cut the list and reverse the second half
        ListNode prev = null;
        ListNode curr = slow.next;
        slow.next = null; // split into two lists

        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        ListNode second = prev; // head of reversed second half

        // 3. merge: alternate nodes from first and second
        ListNode first = head;
        while (second != null) {
            ListNode next1 = first.next;
            ListNode next2 = second.next;

            first.next = second;
            second.next = next1;

            first = next1;
            second = next2;
        }
    }
}
