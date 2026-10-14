use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
        let mut res = Vec::new();

        let mut q = VecDeque::new();
        if let Some(r) = root {
            q.push_back(r);
        }

        while !q.is_empty() {
            let mut cur = Vec::new();

            for _ in 0..q.len() {
                let node = q.pop_front().unwrap();
                let node = node.borrow();

                cur.push(node.val);
                if let Some(l) = &node.left {
                    q.push_back(Rc::clone(l));
                }
                if let Some(r) = &node.right {
                    q.push_back(Rc::clone(r));
                }
            }
            res.push(cur);
        }
        res
    }
}
