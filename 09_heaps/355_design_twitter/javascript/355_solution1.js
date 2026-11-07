class Heap {
  // cmp(a, b) < 0 means a comes out first
  constructor(cmp) {
    this.cmp = cmp;
    this.data = [];
  }

  size() {
    return this.data.length;
  }

  push(val) {
    const h = this.data;
    h.push(val);
    let i = h.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (this.cmp(h[p], h[i]) <= 0) break;
      [h[p], h[i]] = [h[i], h[p]];
      i = p;
    }
  }

  pop() {
    const h = this.data;
    const top = h[0];
    const last = h.pop();
    if (h.length === 0) return top;
    h[0] = last;
    let i = 0;
    for (;;) {
      let best = i;
      const l = 2 * i + 1,
        r = 2 * i + 2;
      if (l < h.length && this.cmp(h[l], h[best]) < 0) best = l;
      if (r < h.length && this.cmp(h[r], h[best]) < 0) best = r;
      if (best === i) return top;
      [h[best], h[i]] = [h[i], h[best]];
      i = best;
    }
  }
}

class Twitter {
  constructor() {
    this.timestamp = 0;
    this.tweets = new Map(); // userId -> [timestamp, tweetId][]
    this.following = new Map(); // userId -> Set of followeeIds
  }

  postTweet(userId, tweetId) {
    if (!this.tweets.has(userId)) this.tweets.set(userId, []);
    this.tweets.get(userId).push([this.timestamp++, tweetId]);
  }

  getNewsFeed(userId) {
    // min-heap of size 10, ordered by timestamp: top is the oldest of the kept
    // tweets
    const pq = new Heap((a, b) => a[0] - b[0]);

    const scan = (uid) => {
      for (const t of this.tweets.get(uid) ?? []) {
        pq.push(t);
        if (pq.size() > 10) pq.pop();
      }
    };

    scan(userId);
    for (const f of this.following.get(userId) ?? [])
      if (f !== userId) scan(f); // avoid scanning own tweets twice

    // heap pops oldest first, so fill the result from the back
    const res = new Array(pq.size());
    for (let i = res.length - 1; i >= 0; i--) res[i] = pq.pop()[1];
    return res;
  }

  follow(followerId, followeeId) {
    if (!this.following.has(followerId)) this.following.set(followerId, new Set());
    this.following.get(followerId).add(followeeId);
  }

  unfollow(followerId, followeeId) {
    this.following.get(followerId)?.delete(followeeId);
  }
}
