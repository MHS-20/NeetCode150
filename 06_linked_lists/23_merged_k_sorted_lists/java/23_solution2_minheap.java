import java.util.PriorityQueue;

class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));

        // seed with the head of each non-empty list
        for (ListNode head : lists)
            if (head != null)
                minHeap.add(head);

        ListNode dummy = new ListNode();
        ListNode cur = dummy;

        while (!minHeap.isEmpty()) {
            ListNode smallest = minHeap.poll();

            cur.next = smallest;
            cur = cur.next;

            // the only new candidate is the successor of the node we just took
            if (smallest.next != null)
                minHeap.add(smallest.next);
        }

        return dummy.next;
    }
}
