use crate::list_node::ListNode;

impl Solution {
    pub fn merge_two_lists(
        mut list1: Option<Box<ListNode>>,
        mut list2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let mut dummy = Box::new(ListNode::new(0));
        let mut tail = &mut dummy;

        loop {
            match (list1, list2) {
                (Some(mut n1), Some(n2)) if n1.val <= n2.val => {
                    list1 = n1.next.take();
                    list2 = Some(n2);
                    tail.next = Some(n1);
                }
                (Some(n1), Some(mut n2)) => {
                    list2 = n2.next.take();
                    list1 = Some(n1);
                    tail.next = Some(n2);
                }
                (Some(n1), None) => {
                    tail.next = Some(n1);
                    break;
                }
                (None, Some(n2)) => {
                    tail.next = Some(n2);
                    break;
                }
                (None, None) => break,
            }
            tail = tail.next.as_mut().unwrap();
        }

        dummy.next
    }
}
