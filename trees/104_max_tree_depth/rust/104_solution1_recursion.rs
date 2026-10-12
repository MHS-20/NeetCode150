use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        Self::find_depth(&root, 0)
    }

    fn find_depth(root: &Option<Rc<RefCell<TreeNode>>>, count: i32) -> i32 {
        match root {
            None => count,
            Some(node) => {
                let n = node.borrow();
                Self::find_depth(&n.left, count + 1).max(Self::find_depth(&n.right, count + 1))
            }
        }
    }
}
