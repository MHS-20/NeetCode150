class TimeMap {
  constructor() {
    this.kv = new Map();
  }

  set(key, value, timestamp) {
    if (!this.kv.has(key)) this.kv.set(key, []);
    this.kv.get(key).push([timestamp, value]);
  }

  get(key, timestamp) {
    const arr = this.kv.get(key);
    if (!arr) return "";

    let left = 0, right = arr.length - 1, resIdx = -1;

    while (left <= right) {
      const mid = left + Math.floor((right - left) / 2);
      const [t, value] = arr[mid];

      if (t === timestamp) return value;
      if (t > timestamp) right = mid - 1;
      else {
        resIdx = mid;
        left = mid + 1;
      }
    }

    return resIdx === -1 ? "" : arr[resIdx][1];
  }
}
