use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn level_order(root: Link) -> Vec<Vec<i32>> {
        let mut res = Vec::new();
        Self::dfs(&root, 0, &mut res);
        res
    }

    fn dfs(node: &Link, depth: usize, res: &mut Vec<Vec<i32>>) {
        if let Some(n) = node {
            let n = n.borrow();

            // create vec for new depth
            if depth == res.len() {
                res.push(Vec::new());
            }

            res[depth].push(n.val);

            Self::dfs(&n.left, depth + 1, res);
            Self::dfs(&n.right, depth + 1, res);
        }
    }
}
