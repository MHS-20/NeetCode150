class MinStack {
  constructor() {
    this.st = []; // [value, minimum of everything up to and including it]
  }

  push(value) {
    const curMin = this.st.length ? Math.min(this.st.at(-1)[1], value) : value;
    this.st.push([value, curMin]);
  }

  pop() {
    this.st.pop();
  }

  top() {
    return this.st.at(-1)[0];
  }

  getMin() {
    return this.st.at(-1)[1];
  }
}
