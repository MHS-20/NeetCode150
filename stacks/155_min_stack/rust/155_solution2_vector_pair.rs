struct MinStack {
    st: Vec<(i32, i32)>, // (value, minimum of everything up to and including it)
}

impl MinStack {
    fn new() -> Self {
        MinStack { st: Vec::new() }
    }

    fn push(&mut self, value: i32) {
        let cur_min = self.st.last().map_or(value, |&(_, m)| m.min(value));
        self.st.push((value, cur_min));
    }

    fn pop(&mut self) {
        self.st.pop();
    }

    fn top(&self) -> i32 {
        self.st.last().unwrap().0
    }

    fn get_min(&self) -> i32 {
        self.st.last().unwrap().1
    }
}
