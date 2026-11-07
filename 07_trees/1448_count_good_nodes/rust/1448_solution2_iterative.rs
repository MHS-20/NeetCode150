use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

impl Solution {
    pub fn good_nodes(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut count = 0;
        let mut stack = vec![(root, i32::MIN)];

        while let Some((node, max_so_far)) = stack.pop() {
            let Some(node) = node else { continue };
            let node = node.borrow();

            let mut max_so_far = max_so_far;
            if node.val >= max_so_far {
                count += 1;
                max_so_far = node.val;
            }

            stack.push((node.left.clone(), max_so_far));
            stack.push((node.right.clone(), max_so_far));
        }
        count
    }
}
