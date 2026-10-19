import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

class Twitter {
    private int timestamp = 0; // global counter, ++ on every postTweet
    private final Map<Integer, List<int[]>> tweets = new HashMap<>(); // userId -> list of {timestamp, tweetId}
    private final Map<Integer, Set<Integer>> following = new HashMap<>(); // userId -> set of followeeIds

    public void postTweet(int userId, int tweetId) {
        tweets.computeIfAbsent(userId, k -> new ArrayList<>()).add(new int[] {timestamp++, tweetId});
    }

    public List<Integer> getNewsFeed(int userId) {
        // {time, tweetId, user, idx}, newest first
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        List<Integer> res = new ArrayList<>();

        Set<Integer> users = new HashSet<>(following.getOrDefault(userId, Set.of()));
        users.add(userId);

        for (int user : users) {
            List<int[]> list = tweets.get(user);
            if (list != null && !list.isEmpty()) {
                int idx = list.size() - 1;
                int[] t = list.get(idx);
                pq.offer(new int[] {t[0], t[1], user, idx});
            }
        }

        while (!pq.isEmpty() && res.size() < 10) {
            int[] e = pq.poll();
            res.add(e[1]);
            int idx = e[3];
            if (idx > 0) {
                int[] t = tweets.get(e[2]).get(idx - 1);
                pq.offer(new int[] {t[0], t[1], e[2], idx - 1});
            }
        }

        return res;
    }

    public void follow(int followerId, int followeeId) {
        following.computeIfAbsent(followerId, k -> new HashSet<>()).add(followeeId);
    }

    public void unfollow(int followerId, int followeeId) {
        following.getOrDefault(followerId, new HashSet<>()).remove(followeeId);
    }
}
