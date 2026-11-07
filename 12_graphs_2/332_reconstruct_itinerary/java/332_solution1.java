import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

class Solution {
    private final Map<String, PriorityQueue<String>> adj = new HashMap<>();
    private final List<String> result = new ArrayList<>();

    private void dfs(String cur) {
        PriorityQueue<String> dests = adj.get(cur);
        while (dests != null && !dests.isEmpty())
            dfs(dests.poll()); // use this ticket
        result.add(cur); // post-order: no tickets left here
    }

    public List<String> findItinerary(List<List<String>> tickets) {
        for (List<String> t : tickets)
            adj.computeIfAbsent(t.get(0), k -> new PriorityQueue<>()).add(t.get(1));

        dfs("JFK");
        Collections.reverse(result);
        return result;
    }
}
