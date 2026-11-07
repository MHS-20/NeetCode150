use std::cell::RefCell;
use std::rc::Rc;

// Definition for a Node (LeetCode has no Rust signature for this problem).
#[derive(Debug)]
pub struct Node {
    pub val: i32,
    pub neighbors: Vec<Rc<RefCell<Node>>>,
}

impl Node {
    #[inline]
    pub fn new(val: i32) -> Self {
        Node {
            val,
            neighbors: Vec::new(),
        }
    }
}
