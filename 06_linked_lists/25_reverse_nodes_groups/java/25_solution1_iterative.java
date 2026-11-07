class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0, head);
        ListNode groupPrev = dummy;

        while (true) {
            // find the k-th node of this group
            ListNode kth = groupPrev;
            for (int i = 0; i < k && kth != null; i++)
                kth = kth.next;
            if (kth == null)
                break; // fewer than k nodes left

            ListNode groupStart = groupPrev.next;
            ListNode groupNext = kth.next; // first node after the group

            // reverse k nodes, starting with prev = groupNext so the
            // old head ends up pointing to the rest of the list
            ListNode prev = groupNext;
            ListNode cur = groupStart;
            while (cur != groupNext) {
                ListNode next = cur.next;
                cur.next = prev;
                prev = cur;
                cur = next;
            }

            groupPrev.next = kth; // previous part -> new group head
            groupPrev = groupStart; // old head is now the group's tail
        }

        return dummy.next;
    }
}
