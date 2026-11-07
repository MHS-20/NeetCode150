use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

impl Solution {
    pub fn build_tree(preorder: Vec<i32>, inorder: Vec<i32>) -> Link {
        let in_index: HashMap<i32, i32> = inorder
            .iter()
            .enumerate()
            .map(|(i, &v)| (v, i as i32))
            .collect();

        let mut pre_idx = 0;
        Self::build(&preorder, &mut pre_idx, 0, inorder.len() as i32 - 1, &in_index)
    }

    fn build(
        preorder: &[i32],
        pre_idx: &mut usize,
        in_lo: i32,
        in_hi: i32,
        in_index: &HashMap<i32, i32>,
    ) -> Link {
        if in_lo > in_hi {
            return None;
        }

        let root_val = preorder[*pre_idx];
        *pre_idx += 1;
        let mid = in_index[&root_val];

        let mut cur = TreeNode::new(root_val);
        cur.left = Self::build(preorder, pre_idx, in_lo, mid - 1, in_index);
        cur.right = Self::build(preorder, pre_idx, mid + 1, in_hi, in_index);
        Some(Rc::new(RefCell::new(cur)))
    }
}
