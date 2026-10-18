use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn max_path_sum(root: Link) -> i32 {
        let mut mx = i32::MIN;
        Self::dfs(&root, &mut mx);
        mx
    }

    fn dfs(node: &Link, mx: &mut i32) -> i32 {
        let Some(n) = node else { return 0 };
        let n = n.borrow();

        let l = Self::dfs(&n.left, mx).max(0);
        let r = Self::dfs(&n.right, mx).max(0);

        *mx = (*mx).max(l + r + n.val);
        l.max(r) + n.val
    }
}
