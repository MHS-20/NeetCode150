use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn right_side_view(root: Link) -> Vec<i32> {
        let mut res = Vec::new();
        Self::dfs(&root, 0, &mut res);
        res
    }

    // visit right first, so the first node seen at each depth is the rightmost
    fn dfs(node: &Link, depth: usize, res: &mut Vec<i32>) {
        if let Some(n) = node {
            let n = n.borrow();

            if depth == res.len() {
                res.push(n.val);
            }

            Self::dfs(&n.right, depth + 1, res);
            Self::dfs(&n.left, depth + 1, res);
        }
    }
}
