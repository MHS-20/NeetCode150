// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
impl Solution {
    pub fn reverse_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        fn helper(
            node: Option<Box<ListNode>>,
            prev: Option<Box<ListNode>>,
        ) -> Option<Box<ListNode>> {
            match node {
                None => prev,
                Some(mut n) => {
                    let next = n.next.take();
                    n.next = prev;
                    helper(next, Some(n))
                }
            }
        }

        helper(head, None)
    }
}
