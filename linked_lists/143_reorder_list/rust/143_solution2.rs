use crate::list_node::ListNode;

impl Solution {
    pub fn reorder_list(head: &mut Option<Box<ListNode>>) {
        // 1. count the nodes to find the end of the first half
        let mut len = 0;
        let mut cur = head.as_ref();
        while let Some(node) = cur {
            len += 1;
            cur = node.next.as_ref();
        }
        if len < 3 {
            return;
        }

        let mut mid = head.as_mut().unwrap();
        for _ in 0..(len - 1) / 2 {
            mid = mid.next.as_mut().unwrap();
        }

        // 2. cut the list and push the second half onto a stack
        let mut stack = Vec::new();
        let mut curr = mid.next.take(); // split into two lists
        while let Some(mut node) = curr {
            curr = node.next.take();
            stack.push(node);
        }

        // 3. merge: popping the stack yields the second half in reverse
        let mut first = head.as_mut();
        while let (Some(node), Some(mut s)) = (first, stack.pop()) {
            s.next = node.next.take();
            node.next = Some(s);
            first = node.next.as_mut().unwrap().next.as_mut();
        }
    }
}
