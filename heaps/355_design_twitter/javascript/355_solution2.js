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
    this.timestamp = 0; // global counter, ++ on every postTweet
    this.tweets = new Map(); // userId -> list of [timestamp, tweetId]
    this.following = new Map(); // userId -> set of followeeIds
  }

  postTweet(userId, tweetId) {
    if (!this.tweets.has(userId)) this.tweets.set(userId, []);
    this.tweets.get(userId).push([this.timestamp++, tweetId]);
  }

  getNewsFeed(userId) {
    // [time, tweetId, user, idx], newest first
    const pq = new Heap((a, b) => b[0] - a[0]);
    const res = [];

    const users = new Set(this.following.get(userId));
    users.add(userId);

    for (const user of users) {
      const list = this.tweets.get(user);
      if (list?.length) {
        const idx = list.length - 1;
        pq.push([...list[idx], user, idx]);
      }
    }

    while (pq.size() > 0 && res.length < 10) {
      const [, tweetId, user, idx] = pq.pop();
      res.push(tweetId);
      if (idx > 0) pq.push([...this.tweets.get(user)[idx - 1], user, idx - 1]);
    }

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
