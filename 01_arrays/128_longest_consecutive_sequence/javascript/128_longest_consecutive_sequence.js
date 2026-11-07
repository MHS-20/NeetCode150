class Solution {
  longestConsecutive(nums) {
    const set = new Set(nums);
    let longest = 0;

    for (const n of set) {
      if (!set.has(n - 1)) {
        let count = 1;

        while (set.has(n + count)) {
          count++;
        }

        longest = Math.max(longest, count);
      }
    }

    return longest;
  }
}
