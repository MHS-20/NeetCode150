use crate::node::{Node, NodeRef};

impl Solution {
    pub fn copy_random_list(head: Option<NodeRef>) -> Option<NodeRef> {
        let head = head?;

        // pass 1: interleave copies
        let mut cur = Some(head.clone());
        while let Some(node) = cur {
            let copy = Node::new(node.borrow().val);
            copy.borrow_mut().next = node.borrow_mut().next.take();
            cur = copy.borrow().next.clone();
            node.borrow_mut().next = Some(copy);
        }

        // pass 2: set random pointers
        let mut cur = Some(head.clone());
        while let Some(node) = cur {
            let orig = node.borrow();
            let copy = orig.next.as_ref().unwrap();
            if let Some(random) = &orig.random {
                copy.borrow_mut().random = random.borrow().next.clone();
            }
            cur = copy.borrow().next.clone();
        }

        // pass 3: separate the lists
        let copy_head = head.borrow().next.clone();
        let mut cur = Some(head);
        while let Some(node) = cur {
            let copy = node.borrow().next.clone().unwrap();
            let next = copy.borrow_mut().next.take();
            if let Some(next) = &next {
                copy.borrow_mut().next = next.borrow().next.clone();
            }
            node.borrow_mut().next = next.clone();
            cur = next;
        }

        copy_head
    }
}
