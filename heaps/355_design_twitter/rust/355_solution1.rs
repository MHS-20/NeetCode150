use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashMap, HashSet};

struct Twitter {
    timestamp: i32,
    tweets: HashMap<i32, Vec<(i32, i32)>>, // userId -> (timestamp, tweetId)
    following: HashMap<i32, HashSet<i32>>, // userId -> followeeIds
}

impl Twitter {
    fn new() -> Self {
        Self { timestamp: 0, tweets: HashMap::new(), following: HashMap::new() }
    }

    fn post_tweet(&mut self, user_id: i32, tweet_id: i32) {
        self.tweets.entry(user_id).or_default().push((self.timestamp, tweet_id));
        self.timestamp += 1;
    }

    fn get_news_feed(&self, user_id: i32) -> Vec<i32> {
        // min-heap of size 10, ordered by timestamp: top is the oldest of the kept tweets
        let mut pq = BinaryHeap::new();

        let mut scan = |uid: i32| {
            for &t in self.tweets.get(&uid).into_iter().flatten() {
                pq.push(Reverse(t));
                if pq.len() > 10 {
                    pq.pop();
                }
            }
        };

        scan(user_id);
        for &f in self.following.get(&user_id).into_iter().flatten() {
            if f != user_id {
                scan(f); // avoid scanning own tweets twice
            }
        }

        // into_sorted_vec is ascending on Reverse, i.e. newest first
        pq.into_sorted_vec().into_iter().map(|Reverse((_, id))| id).collect()
    }

    fn follow(&mut self, follower_id: i32, followee_id: i32) {
        self.following.entry(follower_id).or_default().insert(followee_id);
    }

    fn unfollow(&mut self, follower_id: i32, followee_id: i32) {
        if let Some(set) = self.following.get_mut(&follower_id) {
            set.remove(&followee_id);
        }
    }
}
