class MinStack {
  constructor() {
    this.v = [];
    this.mins = [];
  }

  push(value) {
    this.v.push(value);
    const curMin = this.mins.length ? Math.min(this.mins.at(-1), value) : value;
    this.mins.push(curMin);
  }

  pop() {
    this.v.pop();
    this.mins.pop();
  }

  top() {
    return this.v.at(-1);
  }

  getMin() {
    return this.mins.at(-1);
  }
}
