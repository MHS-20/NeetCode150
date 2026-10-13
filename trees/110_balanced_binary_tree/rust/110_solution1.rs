use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn is_balanced(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        Self::height(&root) != -1
    }

    // returns the subtree height, or -1 as soon as any subtree is unbalanced
    fn height(node: &Option<Rc<RefCell<TreeNode>>>) -> i32 {
        match node {
            None => 0,
            Some(n) => {
                let n = n.borrow();

                let l = Self::height(&n.left);
                if l == -1 {
                    return -1;
                }

                let r = Self::height(&n.right);
                if r == -1 {
                    return -1;
                }

                if (l - r).abs() > 1 {
                    return -1;
                }

                1 + l.max(r)
            }
        }
    }
}
