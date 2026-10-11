use crate::list_node::ListNode;

impl Solution {
    fn merge_two(
        a: Option<Box<ListNode>>,
        b: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        match (a, b) {
            (None, b) => b,
            (a, None) => a,
            (Some(mut a), Some(b)) if a.val <= b.val => {
                a.next = Self::merge_two(a.next.take(), Some(b));
                Some(a)
            }
            (Some(a), Some(mut b)) => {
                b.next = Self::merge_two(Some(a), b.next.take());
                Some(b)
            }
        }
    }

    pub fn merge_k_lists(mut lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        let n = lists.len();
        if n == 0 {
            return None;
        }

        let mut step = 1;
        while step < n {
            let mut i = 0;
            while i + step < n {
                let a = lists[i].take();
                let b = lists[i + step].take();
                lists[i] = Self::merge_two(a, b);
                i += 2 * step;
            }
            step *= 2;
        }

        lists[0].take()
    }
}
