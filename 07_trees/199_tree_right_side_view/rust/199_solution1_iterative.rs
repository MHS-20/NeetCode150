use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn right_side_view(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut res = Vec::new();

        let mut q = VecDeque::new();
        if let Some(r) = root {
            q.push_back(r);
        }

        while !q.is_empty() {
            let sz = q.len();
            for i in 0..sz {
                let node = q.pop_front().unwrap();
                let node = node.borrow();

                if i == sz - 1 {
                    res.push(node.val);
                }

                if let Some(l) = &node.left {
                    q.push_back(Rc::clone(l));
                }
                if let Some(r) = &node.right {
                    q.push_back(Rc::clone(r));
                }
            }
        }
        res
    }
}
