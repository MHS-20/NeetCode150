use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        if let Some(node) = &root {
            let mut n = node.borrow_mut();
            let left = n.left.take();
            let right = n.right.take();

            // invert each subtree, then hang them back swapped
            n.left = Self::invert_tree(right);
            n.right = Self::invert_tree(left);
        }

        root
    }
}
