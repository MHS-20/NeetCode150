use std::collections::VecDeque;

use crate::list_node::ListNode;

impl Solution {
    pub fn reorder_list(head: &mut Option<Box<ListNode>>) {
        // 1. detach every node into a deque
        let mut deque = VecDeque::new();
        let mut curr = head.take();
        while let Some(mut node) = curr {
            curr = node.next.take();
            deque.push_back(node);
        }

        // 2. relink alternating between the front and the back
        let mut tail = head;
        let mut from_front = true;
        loop {
            let node = if from_front {
                deque.pop_front()
            } else {
                deque.pop_back()
            };
            let Some(node) = node else { break };
            from_front = !from_front;

            *tail = Some(node);
            tail = &mut tail.as_mut().unwrap().next;
        }
    }
}
