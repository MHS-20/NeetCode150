use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn kth_smallest(root: Link, k: i32) -> i32 {
        let (mut idx, mut res) = (k, 0);
        Self::dfs(&root, &mut idx, &mut res);
        res
    }

    fn dfs(node: &Link, idx: &mut i32, res: &mut i32) {
        let Some(n) = node else { return };
        if *idx == 0 {
            return;
        }
        let n = n.borrow();

        Self::dfs(&n.left, idx, res);
        *idx -= 1;

        if *idx == 0 {
            *res = n.val;
            return;
        }

        Self::dfs(&n.right, idx, res);
    }
}
