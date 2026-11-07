use std::cell::RefCell;
use std::rc::Rc;

use crate::tree_node::TreeNode;

type Link = Option<Rc<RefCell<TreeNode>>>;

struct Codec {}

impl Codec {
    fn new() -> Self {
        Codec {}
    }

    fn serialize(&self, root: Link) -> String {
        let mut ser = String::new();
        Self::ser_dfs(&root, &mut ser);
        ser
    }

    fn ser_dfs(node: &Link, ser: &mut String) {
        match node {
            None => ser.push_str("N#"),
            Some(n) => {
                let n = n.borrow();
                ser.push_str(&format!("{}#", n.val));
                Self::ser_dfs(&n.left, ser);
                Self::ser_dfs(&n.right, ser);
            }
        }
    }

    fn deserialize(&self, data: String) -> Link {
        let mut tokens = data.split('#');
        Self::des_dfs(&mut tokens)
    }

    fn des_dfs<'a>(tokens: &mut impl Iterator<Item = &'a str>) -> Link {
        let tok = tokens.next()?;
        if tok == "N" {
            return None;
        }

        let mut node = TreeNode::new(tok.parse().unwrap());
        node.left = Self::des_dfs(tokens); // consumes the left subtree's tokens
        node.right = Self::des_dfs(tokens); // continues from there
        Some(Rc::new(RefCell::new(node)))
    }
}
