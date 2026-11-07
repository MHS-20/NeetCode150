package heaps

import "container/heap"

type tweet struct{ time, id int }

// min-heap ordered by timestamp
type tweetHeap []tweet

func (h tweetHeap) Len() int           { return len(h) }
func (h tweetHeap) Less(i, j int) bool { return h[i].time < h[j].time }
func (h tweetHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *tweetHeap) Push(x any)        { *h = append(*h, x.(tweet)) }

func (h *tweetHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

type Twitter struct {
	timestamp int
	tweets    map[int][]tweet          // userId -> tweets in post order
	following map[int]map[int]struct{} // userId -> followeeIds
}

func Constructor() Twitter {
	return Twitter{tweets: map[int][]tweet{}, following: map[int]map[int]struct{}{}}
}

func (this *Twitter) PostTweet(userId int, tweetId int) {
	this.tweets[userId] = append(this.tweets[userId], tweet{this.timestamp, tweetId})
	this.timestamp++
}

func (this *Twitter) GetNewsFeed(userId int) []int {
	// min-heap of size 10: top is the oldest of the kept tweets
	pq := &tweetHeap{}

	scan := func(uid int) {
		for _, t := range this.tweets[uid] {
			heap.Push(pq, t)
			if pq.Len() > 10 {
				heap.Pop(pq)
			}
		}
	}

	scan(userId)
	for f := range this.following[userId] {
		if f != userId {
			scan(f) // avoid scanning own tweets twice
		}
	}

	// heap pops oldest first, so fill the result from the back
	res := make([]int, pq.Len())
	for i := len(res) - 1; i >= 0; i-- {
		res[i] = heap.Pop(pq).(tweet).id
	}
	return res
}

func (this *Twitter) Follow(followerId int, followeeId int) {
	if this.following[followerId] == nil {
		this.following[followerId] = map[int]struct{}{}
	}
	this.following[followerId][followeeId] = struct{}{}
}

func (this *Twitter) Unfollow(followerId int, followeeId int) {
	delete(this.following[followerId], followeeId)
}
