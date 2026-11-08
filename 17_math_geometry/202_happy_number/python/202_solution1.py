class Solution:
    def next(self, n: int) -> int:
        total = 0
        while n > 0:
            n, d = divmod(n, 10)
            total += d * d
        return total

    def isHappy(self, n: int) -> bool:
        slow, fast = n, self.next(n)
        while fast != 1 and slow != fast:
            slow = self.next(slow)
            fast = self.next(self.next(fast))
        return fast == 1
