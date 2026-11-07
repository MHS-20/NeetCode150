use std::collections::HashMap;
use std::rc::Rc;

use crate::node::{Node, NodeRef};

impl Solution {
    pub fn copy_random_list(head: Option<NodeRef>) -> Option<NodeRef> {
        // originals are keyed by address
        let mut copy_of = HashMap::new();

        // pass 1: create all copies (no links yet)
        let mut cur = head.clone();
        while let Some(node) = cur {
            copy_of.insert(Rc::as_ptr(&node), Node::new(node.borrow().val));
            cur = node.borrow().next.clone();
        }

        // None original -> None copy
        let copy = |n: &Option<NodeRef>| n.as_ref().map(|n| copy_of[&Rc::as_ptr(n)].clone());

        // pass 2: wire up next and random
        let mut cur = head.clone();
        while let Some(node) = cur {
            let orig = node.borrow();
            let mut c = copy_of[&Rc::as_ptr(&node)].borrow_mut();
            c.next = copy(&orig.next);
            c.random = copy(&orig.random);
            cur = orig.next.clone();
        }

        copy(&head)
    }
}
