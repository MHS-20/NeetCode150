package main

type entry struct {
	timestamp int
	value     string
}

type TimeMap struct {
	kv map[string][]entry
}

func Constructor() TimeMap {
	return TimeMap{kv: make(map[string][]entry)}
}

func (t *TimeMap) Set(key string, value string, timestamp int) {
	t.kv[key] = append(t.kv[key], entry{timestamp, value})
}

func (t *TimeMap) Get(key string, timestamp int) string {
	arr, ok := t.kv[key]
	if !ok {
		return ""
	}

	left, right, resIdx := 0, len(arr)-1, -1

	for left <= right {
		mid := left + (right-left)/2

		if arr[mid].timestamp == timestamp {
			return arr[mid].value
		}
		if arr[mid].timestamp > timestamp {
			right = mid - 1
		} else {
			resIdx = mid
			left = mid + 1
		}
	}

	if resIdx == -1 {
		return ""
	}
	return arr[resIdx].value
}
