use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut stack = Vec::new();
        if let Some(r) = &root {
            stack.push(Rc::clone(r));
        }

        while let Some(cur) = stack.pop() {
            let mut n = cur.borrow_mut();

            let n = &mut *n;
            std::mem::swap(&mut n.left, &mut n.right);

            if let Some(l) = &n.left {
                stack.push(Rc::clone(l));
            }
            if let Some(r) = &n.right {
                stack.push(Rc::clone(r));
            }
        }

        root
    }
}
