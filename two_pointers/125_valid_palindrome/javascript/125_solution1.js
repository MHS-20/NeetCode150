class Solution {
  isPalindrome(s) {
    const isAlnum = (c) => /[a-zA-Z0-9]/.test(c);
    let left = 0;
    let right = s.length - 1;

    while (left < right) {
      while (left < right && !isAlnum(s[left])) left++;
      while (left < right && !isAlnum(s[right])) right--;

      if (s[left].toLowerCase() !== s[right].toLowerCase()) return false;

      left++;
      right--;
    }

    return true;
  }
}
