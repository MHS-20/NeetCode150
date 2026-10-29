use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

use crate::node::Node;

type NodeRef = Rc<RefCell<Node>>;

impl Solution {
    pub fn clone_graph(node: Option<NodeRef>) -> Option<NodeRef> {
        // keyed by address: Rc identity, not value equality
        let mut clones = HashMap::new();
        node.map(|n| Self::clone(&n, &mut clones))
    }

    fn clone(node: &NodeRef, clones: &mut HashMap<*const RefCell<Node>, NodeRef>) -> NodeRef {
        if let Some(copy) = clones.get(&Rc::as_ptr(node)) {
            return copy.clone();
        }

        let copy = Rc::new(RefCell::new(Node::new(node.borrow().val)));
        clones.insert(Rc::as_ptr(node), copy.clone());
        for cur in node.borrow().neighbors.iter() {
            let neighbor = Self::clone(cur, clones);
            copy.borrow_mut().neighbors.push(neighbor);
        }

        copy
    }
}
