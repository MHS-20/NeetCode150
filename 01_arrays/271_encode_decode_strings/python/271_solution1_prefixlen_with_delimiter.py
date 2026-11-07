class Solution:
    def encode(self, strs: list[str]) -> str:
        encoded = ""
        for s in strs:
            encoded += str(len(s)) + "-" + s
        return encoded

    def decode(self, s: str) -> list[str]:
        res = []
        i = 0

        while i < len(s):
            delim_pos = s.find("-", i)
            length = int(s[i:delim_pos])

            res.append(s[delim_pos + 1 : delim_pos + 1 + length])
            i = delim_pos + 1 + length

        return res
