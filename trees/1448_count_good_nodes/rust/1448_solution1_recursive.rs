use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn good_nodes(root: Link) -> i32 {
        let mut count = 0;
        Self::dfs(&root, i32::MIN, &mut count);
        count
    }

    fn dfs(node: &Link, max_so_far: i32, count: &mut i32) {
        if let Some(n) = node {
            let n = n.borrow();

            let mut max_so_far = max_so_far;
            if n.val >= max_so_far {
                *count += 1;
                max_so_far = n.val;
            }
            Self::dfs(&n.left, max_so_far, count);
            Self::dfs(&n.right, max_so_far, count);
        }
    }
}
