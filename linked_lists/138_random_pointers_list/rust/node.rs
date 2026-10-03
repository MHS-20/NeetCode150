use std::cell::RefCell;
use std::rc::Rc;

// Definition for a Node.
// LeetCode has no Rust version of this problem; shared ownership is needed
// because several nodes can point at the same node through `random`.
pub type NodeRef = Rc<RefCell<Node>>;

pub struct Node {
    pub val: i32,
    pub next: Option<NodeRef>,
    pub random: Option<NodeRef>,
}

impl Node {
    pub fn new(val: i32) -> NodeRef {
        Rc::new(RefCell::new(Node {
            val,
            next: None,
            random: None,
        }))
    }
}
