use crate::list_node::ListNode;

impl Solution {
    pub fn merge_two_lists(
        a: Option<Box<ListNode>>,
        b: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        match (a, b) {
            (None, b) => b,
            (a, None) => a,
            (Some(mut a), Some(b)) if a.val <= b.val => {
                a.next = Self::merge_two_lists(a.next.take(), Some(b));
                Some(a)
            }
            (Some(a), Some(mut b)) => {
                b.next = Self::merge_two_lists(Some(a), b.next.take());
                Some(b)
            }
        }
    }
}
