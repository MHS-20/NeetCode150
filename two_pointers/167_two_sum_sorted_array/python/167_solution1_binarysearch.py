class Solution:
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        for idx in range(len(numbers)):
            diff = target - numbers[idx]
            i, j = idx + 1, len(numbers) - 1

            while i <= j:
                mid = (i + j) // 2

                if numbers[mid] == diff:
                    return [idx + 1, mid + 1]

                if numbers[mid] > diff:
                    j = mid - 1
                else:
                    i = mid + 1

        return []
