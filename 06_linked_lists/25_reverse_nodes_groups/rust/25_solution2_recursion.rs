use crate::list_node::ListNode;

impl Solution {
    pub fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        let k = k as usize;

        // check that k nodes exist
        let mut p = &head;
        for _ in 0..k {
            match p {
                None => return head, // fewer than k: leave as is
                Some(node) => p = &node.next,
            }
        }

        // detach the rest after the k-th node
        let mut head = head;
        let mut p = &mut head;
        for _ in 0..k {
            p = &mut p.as_mut().unwrap().next;
        }
        let rest = p.take();

        let mut prev = Self::reverse_k_group(rest, k as i32); // already-processed rest
        let mut cur = head;
        while let Some(mut node) = cur {
            cur = node.next.take();
            node.next = prev;
            prev = Some(node);
        }
        prev // new head of this group
    }
}
