use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut q = VecDeque::new();
        if let Some(r) = root {
            q.push_back(r);
        }

        let mut depth = 0;
        while !q.is_empty() {
            depth += 1;

            for _ in 0..q.len() {
                let cur = q.pop_front().unwrap();
                let n = cur.borrow();

                if let Some(l) = &n.left {
                    q.push_back(Rc::clone(l));
                }
                if let Some(r) = &n.right {
                    q.push_back(Rc::clone(r));
                }
            }
        }

        depth
    }
}
