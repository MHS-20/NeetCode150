class MinStack:
    def __init__(self):
        self.st = []  # (value, minimum of everything up to and including it)

    def push(self, value: int) -> None:
        cur_min = min(self.st[-1][1], value) if self.st else value
        self.st.append((value, cur_min))

    def pop(self) -> None:
        self.st.pop()

    def top(self) -> int:
        return self.st[-1][0]

    def getMin(self) -> int:
        return self.st[-1][1]
