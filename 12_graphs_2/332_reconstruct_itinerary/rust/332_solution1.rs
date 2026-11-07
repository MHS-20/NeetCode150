use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashMap};

impl Solution {
    pub fn find_itinerary(tickets: Vec<Vec<String>>) -> Vec<String> {
        // airport -> min-heap of destinations
        let mut adj: HashMap<String, BinaryHeap<Reverse<String>>> = HashMap::new();
        for t in tickets {
            adj.entry(t[0].clone()).or_default().push(Reverse(t[1].clone()));
        }

        let mut result = Vec::new();
        Self::dfs("JFK".to_string(), &mut adj, &mut result);
        result.reverse();
        result
    }

    fn dfs(cur: String, adj: &mut HashMap<String, BinaryHeap<Reverse<String>>>, result: &mut Vec<String>) {
        while let Some(Reverse(next)) = adj.get_mut(&cur).and_then(|dests| dests.pop()) {
            Self::dfs(next, adj, result); // use this ticket
        }
        result.push(cur); // post-order: no tickets left here
    }
}
