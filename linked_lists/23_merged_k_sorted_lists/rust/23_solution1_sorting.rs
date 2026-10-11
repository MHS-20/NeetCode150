use crate::list_node::ListNode;

impl Solution {
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        // 1. collect every value from every list
        let mut vals = Vec::new();
        for head in &lists {
            let mut p = head;
            while let Some(node) = p {
                vals.push(node.val);
                p = &node.next;
            }
        }

        // 2. sort them
        vals.sort_unstable();

        // 3. rebuild a new list (back to front, so no tail pointer is needed)
        let mut head = None;
        for v in vals.into_iter().rev() {
            let mut node = Box::new(ListNode::new(v));
            node.next = head;
            head = Some(node);
        }

        head
    }
}
