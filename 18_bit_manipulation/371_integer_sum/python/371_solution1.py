class Solution:
    def getSum(self, a: int, b: int) -> int:
        # Python ints are unbounded: mask to 32 bits so the carry dies after bit 31
        M = 0xFFFFFFFF
        total, carry = (a ^ b) & M, ((a & b) << 1) & M

        while carry != 0:
            tmp = ((total & carry) << 1) & M
            total ^= carry
            carry = tmp

        # reinterpret the 32-bit pattern as signed
        return total if total <= 0x7FFFFFFF else ~(total ^ M)
