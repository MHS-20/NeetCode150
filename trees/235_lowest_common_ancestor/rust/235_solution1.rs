use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn lowest_common_ancestor(
        root: Option<Rc<RefCell<TreeNode>>>,
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let (pv, qv) = (p?.borrow().val, q?.borrow().val);
        let (lo, hi) = (pv.min(qv), pv.max(qv));

        // the LCA is the first node whose value falls between p and q
        let mut cur = root;
        while let Some(node) = cur {
            let val = node.borrow().val;
            if val < lo {
                cur = node.borrow().right.clone();
            } else if val > hi {
                cur = node.borrow().left.clone();
            } else {
                return Some(node);
            }
        }

        None
    }
}
