use std::cmp::{Ordering, Reverse};
use std::collections::BinaryHeap;

use crate::list_node::ListNode;

// orders nodes by val only, so ListNode itself needs no Ord
struct HeapNode(Box<ListNode>);

impl PartialEq for HeapNode {
    fn eq(&self, other: &Self) -> bool {
        self.0.val == other.0.val
    }
}
impl Eq for HeapNode {}
impl PartialOrd for HeapNode {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}
impl Ord for HeapNode {
    fn cmp(&self, other: &Self) -> Ordering {
        self.0.val.cmp(&other.0.val)
    }
}

impl Solution {
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        // seed with the head of each non-empty list
        let mut min_heap: BinaryHeap<Reverse<HeapNode>> = lists
            .into_iter()
            .flatten()
            .map(|head| Reverse(HeapNode(head)))
            .collect();

        let mut dummy = Box::new(ListNode::new(0));
        let mut tail = &mut dummy;

        while let Some(Reverse(HeapNode(mut smallest))) = min_heap.pop() {
            // the only new candidate is the successor of the node we just took
            if let Some(next) = smallest.next.take() {
                min_heap.push(Reverse(HeapNode(next)));
            }

            tail.next = Some(smallest);
            tail = tail.next.as_mut().unwrap();
        }

        dummy.next
    }
}
