package graphs

import "sort"

func findItinerary(tickets [][]string) []string {
	// destinations sorted descending, so popping from the back yields the smallest
	adj := map[string][]string{}
	for _, t := range tickets {
		adj[t[0]] = append(adj[t[0]], t[1])
	}
	for _, dests := range adj {
		sort.Sort(sort.Reverse(sort.StringSlice(dests)))
	}

	result := []string{}
	var dfs func(cur string)
	dfs = func(cur string) {
		for len(adj[cur]) > 0 {
			dests := adj[cur]
			next := dests[len(dests)-1]
			adj[cur] = dests[:len(dests)-1] // use this ticket
			dfs(next)
		}
		result = append(result, cur) // post-order: no tickets left here
	}

	dfs("JFK")
	for i, j := 0, len(result)-1; i < j; i, j = i+1, j-1 {
		result[i], result[j] = result[j], result[i]
	}
	return result
}
