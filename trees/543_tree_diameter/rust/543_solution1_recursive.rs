use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn diameter_of_binary_tree(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut best = 0;
        Self::height(&root, &mut best);
        best
    }

    fn height(node: &Option<Rc<RefCell<TreeNode>>>, best: &mut i32) -> i32 {
        match node {
            None => 0,
            Some(n) => {
                let n = n.borrow();
                let l = Self::height(&n.left, best);
                let r = Self::height(&n.right, best);

                *best = (*best).max(l + r);
                1 + l.max(r)
            }
        }
    }
}
