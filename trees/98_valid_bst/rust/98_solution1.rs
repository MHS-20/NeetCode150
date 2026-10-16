use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn is_valid_bst(root: Link) -> bool {
        Self::dfs(&root, i64::MIN, i64::MAX)
    }

    fn dfs(node: &Link, lowerbound: i64, upperbound: i64) -> bool {
        match node {
            None => true,
            Some(n) => {
                let n = n.borrow();
                let val = n.val as i64;
                if val <= lowerbound || val >= upperbound {
                    return false;
                }
                Self::dfs(&n.right, val, upperbound) && Self::dfs(&n.left, lowerbound, val)
            }
        }
    }
}
