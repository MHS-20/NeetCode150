use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn is_subtree(root: Link, sub_root: Link) -> bool {
        Self::contains(&root, &sub_root)
    }

    fn contains(root: &Link, sub_root: &Link) -> bool {
        if sub_root.is_none() {
            return true;
        }
        match root {
            None => false,
            Some(n) => {
                let n = n.borrow();
                Self::is_same_tree(root, sub_root)
                    || Self::contains(&n.left, sub_root)
                    || Self::contains(&n.right, sub_root)
            }
        }
    }

    fn is_same_tree(r1: &Link, r2: &Link) -> bool {
        match (r1, r2) {
            (None, None) => true,
            (Some(a), Some(b)) => {
                let (a, b) = (a.borrow(), b.borrow());
                a.val == b.val
                    && Self::is_same_tree(&a.left, &b.left)
                    && Self::is_same_tree(&a.right, &b.right)
            }
            _ => false,
        }
    }
}
