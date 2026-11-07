use std::cell::RefCell;
use std::collections::HashMap;
use std::collections::VecDeque;
use std::rc::Rc;

use crate::node::Node;

type NodeRef = Rc<RefCell<Node>>;

impl Solution {
    pub fn clone_graph(node: Option<NodeRef>) -> Option<NodeRef> {
        let node = node?;

        // keyed by address: Rc identity, not value equality
        let mut clones: HashMap<*const RefCell<Node>, NodeRef> = HashMap::new();
        let root = Rc::new(RefCell::new(Node::new(node.borrow().val)));
        clones.insert(Rc::as_ptr(&node), root.clone());
        let mut q = VecDeque::from([node.clone()]);

        while let Some(cur) = q.pop_front() {
            for neighbor in cur.borrow().neighbors.iter() {
                let key = Rc::as_ptr(neighbor);
                if !clones.contains_key(&key) {
                    let copy = Rc::new(RefCell::new(Node::new(neighbor.borrow().val)));
                    clones.insert(key, copy);
                    q.push_back(neighbor.clone());
                }
                let copy = clones[&key].clone();
                clones[&Rc::as_ptr(&cur)].borrow_mut().neighbors.push(copy);
            }
        }
        Some(root)
    }
}
