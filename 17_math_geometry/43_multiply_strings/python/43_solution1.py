class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        n, m = len(num1), len(num2)
        pos = [0] * (n + m)

        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                mul = int(num1[i]) * int(num2[j])
                total = mul + pos[i + j + 1]
                pos[i + j + 1] = total % 10  # ones digit stays here
                pos[i + j] += total // 10  # carry goes one position left

        res = "".join(map(str, pos)).lstrip("0")  # skip leading zeros
        return res or "0"
