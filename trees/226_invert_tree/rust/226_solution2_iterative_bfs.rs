use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut q = VecDeque::new();
        if let Some(r) = &root {
            q.push_back(Rc::clone(r));
        }

        while let Some(cur) = q.pop_front() {
            let mut n = cur.borrow_mut();

            let n = &mut *n;
            std::mem::swap(&mut n.left, &mut n.right);

            if let Some(l) = &n.left {
                q.push_back(Rc::clone(l));
            }
            if let Some(r) = &n.right {
                q.push_back(Rc::clone(r));
            }
        }

        root
    }
}
