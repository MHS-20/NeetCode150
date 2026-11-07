class Solution:
    def carFleet(self, target: int, position: list[int], speed: list[int]) -> int:
        fleets = 0
        slowest = 0.0  # arrival time of the fleet ahead

        for p, s in sorted(zip(position, speed), reverse=True):
            hours = (target - p) / s
            if hours > slowest:
                fleets += 1
                slowest = hours
        return fleets
