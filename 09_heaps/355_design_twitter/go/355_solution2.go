package heaps

import "container/heap"

type tweet struct{ time, id int }

type entry struct{ time, id, user, idx int }

// max-heap ordered by timestamp
type entryHeap []entry

func (h entryHeap) Len() int           { return len(h) }
func (h entryHeap) Less(i, j int) bool { return h[i].time > h[j].time }
func (h entryHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *entryHeap) Push(x any)        { *h = append(*h, x.(entry)) }

func (h *entryHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

type Twitter struct {
	timestamp int                      // global counter, ++ on every PostTweet
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
	pq := &entryHeap{}
	res := []int{}

	push := func(user, idx int) {
		t := this.tweets[user][idx]
		heap.Push(pq, entry{t.time, t.id, user, idx})
	}

	if n := len(this.tweets[userId]); n > 0 {
		push(userId, n-1)
	}
	for user := range this.following[userId] {
		if n := len(this.tweets[user]); user != userId && n > 0 {
			push(user, n-1)
		}
	}

	for pq.Len() > 0 && len(res) < 10 {
		e := heap.Pop(pq).(entry)
		res = append(res, e.id)
		if e.idx > 0 {
			push(e.user, e.idx-1)
		}
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
