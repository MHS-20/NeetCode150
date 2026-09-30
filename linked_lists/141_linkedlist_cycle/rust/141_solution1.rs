// A cyclic list cannot be expressed with the crate's usual
// `Option<Box<ListNode>>` definition (Box ownership forbids cycles), so this
// problem uses LeetCode's raw-pointer node definition instead of list_node.rs.
//
// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//     pub val: i32,
//     pub next: *mut ListNode,
// }
impl Solution {
    pub unsafe fn has_cycle(head: *mut ListNode) -> bool {
        let mut slow = head;
        let mut fast = head;

        while !fast.is_null() && !(*fast).next.is_null() {
            slow = (*slow).next;
            fast = (*(*fast).next).next;

            if slow == fast {
                return true;
            }
        }

        false
    }
}
