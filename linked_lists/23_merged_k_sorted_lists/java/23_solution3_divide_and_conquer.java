class Solution {
    private ListNode mergeTwo(ListNode a, ListNode b) {
        ListNode dummy = new ListNode();
        ListNode cur = dummy;
        while (a != null && b != null) {
            if (a.val <= b.val) {
                cur.next = a;
                a = a.next;
            } else {
                cur.next = b;
                b = b.next;
            }
            cur = cur.next;
        }
        cur.next = (a != null) ? a : b;
        return dummy.next;
    }

    public ListNode mergeKLists(ListNode[] lists) {
        int n = lists.length;
        if (n == 0)
            return null;

        for (int step = 1; step < n; step *= 2)
            for (int i = 0; i + step < n; i += 2 * step)
                lists[i] = mergeTwo(lists[i], lists[i + step]);

        return lists[0];
    }
}
