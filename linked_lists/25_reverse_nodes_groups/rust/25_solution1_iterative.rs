use crate::list_node::ListNode;

impl Solution {
    pub fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        let k = k as usize;

        let mut len = 0;
        let mut p = &head;
        while let Some(node) = p {
            len += 1;
            p = &node.next;
        }

        let mut dummy = Box::new(ListNode::new(0));
        dummy.next = head;
        let mut tail = &mut dummy;

        for _ in 0..len / k {
            // reverse the k nodes after tail
            let mut cur = tail.next.take();
            let mut prev = None;
            for _ in 0..k {
                let mut node = cur.unwrap();
                cur = node.next.take();
                node.next = prev;
                prev = Some(node);
            }
            tail.next = prev;

            // old head is now the group's tail; reattach the rest
            for _ in 0..k {
                tail = tail.next.as_mut().unwrap();
            }
            tail.next = cur;
        }

        dummy.next
    }
}
