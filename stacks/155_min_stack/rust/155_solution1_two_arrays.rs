struct MinStack {
    v: Vec<i32>,
    mins: Vec<i32>,
}

impl MinStack {
    fn new() -> Self {
        MinStack { v: Vec::new(), mins: Vec::new() }
    }

    fn push(&mut self, value: i32) {
        self.v.push(value);

        let cur_min = self.mins.last().map_or(value, |&m| m.min(value));
        self.mins.push(cur_min);
    }

    fn pop(&mut self) {
        self.v.pop();
        self.mins.pop();
    }

    fn top(&self) -> i32 {
        *self.v.last().unwrap()
    }

    fn get_min(&self) -> i32 {
        *self.mins.last().unwrap()
    }
}
