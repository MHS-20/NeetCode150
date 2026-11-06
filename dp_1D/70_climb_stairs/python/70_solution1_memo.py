class Solution:
    def climbStairs(self, n: int) -> int:
        memo = [-1] * (n + 1)

        def ways(i: int) -> int:
            if i <= 2:
                return i  # ways(1) = 1, ways(2) = 2
            if memo[i] != -1:
                return memo[i]
            memo[i] = ways(i - 1) + ways(i - 2)
            return memo[i]

        return ways(n)
