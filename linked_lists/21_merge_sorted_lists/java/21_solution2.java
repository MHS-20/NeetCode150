class Solution {
    public ListNode mergeTwoLists(ListNode a, ListNode b) {
        if (a == null)
            return b;
        if (b == null)
            return a;
        if (a.val <= b.val) {
            a.next = mergeTwoLists(a.next, b);
            return a;
        }
        b.next = mergeTwoLists(a, b.next);
        return b;
    }
}
