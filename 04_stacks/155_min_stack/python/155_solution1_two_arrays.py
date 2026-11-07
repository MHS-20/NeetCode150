class MinStack:
    def __init__(self):
        self.v = []
        self.mins = []

    def push(self, value: int) -> None:
        self.v.append(value)
        self.mins.append(min(self.mins[-1], value) if self.mins else value)

    def pop(self) -> None:
        self.v.pop()
        self.mins.pop()

    def top(self) -> int:
        return self.v[-1]

    def getMin(self) -> int:
        return self.mins[-1]
