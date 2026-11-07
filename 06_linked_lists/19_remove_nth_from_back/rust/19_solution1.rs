use crate::list_node::ListNode;

impl Solution {
    pub fn remove_nth_from_end(head: Option<Box<ListNode>>, n: i32) -> Option<Box<ListNode>> {
        let mut dummy = Box::new(ListNode { val: 0, next: head });

        // count the nodes to find the index of the node before the target
        let mut len = 0;
        let mut cur = dummy.next.as_ref();
        while let Some(node) = cur {
            len += 1;
            cur = node.next.as_ref();
        }

        let mut prev = &mut dummy;
        for _ in 0..(len - n) {
            prev = prev.next.as_mut().unwrap();
        }

        let target = prev.next.take();
        prev.next = target.and_then(|node| node.next);

        dummy.next
    }
}
