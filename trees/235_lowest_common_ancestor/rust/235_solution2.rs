use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn lowest_common_ancestor(
        root: Option<Rc<RefCell<TreeNode>>>,
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let (pv, qv) = (p.as_ref()?.borrow().val, q.as_ref()?.borrow().val);
        if pv > qv {
            return Self::lowest_common_ancestor(root, q, p);
        }

        let node = root?;
        let val = node.borrow().val;
        if val >= pv && val <= qv {
            return Some(node);
        }

        let next = if qv < val {
            node.borrow().left.clone()
        } else {
            node.borrow().right.clone()
        };
        Self::lowest_common_ancestor(next, p, q)
    }
}
