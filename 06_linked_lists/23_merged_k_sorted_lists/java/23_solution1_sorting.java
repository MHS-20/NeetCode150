import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        // 1. collect every value from every list
        List<Integer> vals = new ArrayList<>();
        for (ListNode head : lists)
            for (ListNode p = head; p != null; p = p.next)
                vals.add(p.val);

        // 2. sort them
        int[] sorted = vals.stream().mapToInt(Integer::intValue).toArray();
        Arrays.sort(sorted);

        // 3. rebuild a new list
        ListNode dummy = new ListNode();
        ListNode cur = dummy;
        for (int v : sorted) {
            cur.next = new ListNode(v);
            cur = cur.next;
        }

        return dummy.next;
    }
}
