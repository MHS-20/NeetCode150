class Solution {
    public int getSum(int a, int b) {
        // Java ints wrap on overflow, so no unsigned type is needed
        int sum = a ^ b, carry = (a & b) << 1;

        while (carry != 0) {
            int tmp = (sum & carry) << 1;
            sum ^= carry;
            carry = tmp;
        }

        return sum;
    }
}
