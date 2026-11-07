import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

class Twitter {
    private int timestamp = 0;
    private final Map<Integer, List<int[]>> tweets = new HashMap<>(); // userId -> {timestamp, tweetId}
    private final Map<Integer, Set<Integer>> following = new HashMap<>(); // userId -> followeeIds

    public void postTweet(int userId, int tweetId) {
        tweets.computeIfAbsent(userId, k -> new ArrayList<>()).add(new int[] {timestamp++, tweetId});
    }

    public List<Integer> getNewsFeed(int userId) {
        // min-heap of size 10, ordered by timestamp: top is the oldest of the kept tweets
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);

        scan(userId, pq);
        for (int f : following.getOrDefault(userId, Set.of()))
            if (f != userId)
                scan(f, pq); // avoid scanning own tweets twice

        // heap pops oldest first, so fill the result from the back
        Integer[] res = new Integer[pq.size()];
        for (int i = res.length - 1; i >= 0; i--)
            res[i] = pq.poll()[1];
        return List.of(res);
    }

    private void scan(int uid, PriorityQueue<int[]> pq) {
        for (int[] t : tweets.getOrDefault(uid, List.of())) {
            pq.offer(t);
            if (pq.size() > 10)
                pq.poll();
        }
    }

    public void follow(int followerId, int followeeId) {
        following.computeIfAbsent(followerId, k -> new HashSet<>()).add(followeeId);
    }

    public void unfollow(int followerId, int followeeId) {
        following.getOrDefault(followerId, new HashSet<>()).remove(followeeId);
    }
}
