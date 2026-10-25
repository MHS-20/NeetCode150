use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn lowest_common_ancestor(
        root: Option<Rc<RefCell<TreeNode>>>,
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let (mut pv, mut qv) = (p?.borrow().val, q?.borrow().val);
        if pv > qv {
            std::mem::swap(&mut pv, &mut qv);
        }

        let mut cur = root;
        while let Some(node) = cur {
            let val = node.borrow().val;
            if val >= pv && val <= qv {
                return Some(node);
            }

            if val < pv {
                cur = node.borrow().right.clone();
            } else {
                cur = node.borrow().left.clone();
            }
        }

        None
    }
}
