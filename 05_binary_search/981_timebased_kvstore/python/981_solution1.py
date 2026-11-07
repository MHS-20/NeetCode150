class TimeMap:
    def __init__(self):
        self.kv: dict[str, list[tuple[int, str]]] = {}

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.kv.setdefault(key, []).append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        arr = self.kv.get(key)
        if not arr:
            return ""

        left, right, resIdx = 0, len(arr) - 1, -1

        while left <= right:
            mid = left + (right - left) // 2
            if arr[mid][0] == timestamp:
                return arr[mid][1]
            if arr[mid][0] > timestamp:
                right = mid - 1
            else:
                resIdx = mid
                left = mid + 1

        return "" if resIdx == -1 else arr[resIdx][1]
