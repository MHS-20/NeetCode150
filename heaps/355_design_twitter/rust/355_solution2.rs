use std::collections::{BinaryHeap, HashMap, HashSet};

struct Twitter {
    timestamp: i32,                        // global counter, += 1 on every post_tweet
    tweets: HashMap<i32, Vec<(i32, i32)>>, // userId -> list of (timestamp, tweetId)
    following: HashMap<i32, HashSet<i32>>, // userId -> set of followeeIds
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
        let mut pq = BinaryHeap::new(); // (time, tweetId, user, idx)
        let mut res = Vec::new();

        let followees = self.following.get(&user_id).into_iter().flatten();
        let users: HashSet<i32> = followees.copied().chain([user_id]).collect();

        for user in users {
            if let Some(list) = self.tweets.get(&user).filter(|l| !l.is_empty()) {
                let idx = list.len() - 1;
                let (time, tweet_id) = list[idx];
                pq.push((time, tweet_id, user, idx));
            }
        }

        while res.len() < 10 {
            let Some((_, tweet_id, user, idx)) = pq.pop() else { break };
            res.push(tweet_id);
            if idx > 0 {
                let (time, tweet_id) = self.tweets[&user][idx - 1];
                pq.push((time, tweet_id, user, idx - 1));
            }
        }

        res
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
