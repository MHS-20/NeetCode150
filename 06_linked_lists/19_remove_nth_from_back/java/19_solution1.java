class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0, head);
        ListNode left = dummy;
        ListNode right = dummy;

        // create a gap of n nodes between left and right
        for (int i = 0; i < n; i++)
            right = right.next;

        // move both until right is on the last node;
        // left is then on the node before the target
        while (right.next != null) {
            right = right.next;
            left = left.next;
        }

        left.next = left.next.next;

        return dummy.next;
    }
}
