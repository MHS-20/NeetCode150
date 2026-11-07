class Solution {
  carFleet(target, position, speed) {
    const cars = position
      .map((p, i) => [p, speed[i]])
      .sort((a, b) => b[0] - a[0]);

    let fleets = 0;
    let slowest = 0; // arrival time of the fleet ahead
    for (const [p, s] of cars) {
      const hours = (target - p) / s;
      if (hours > slowest) {
        fleets++;
        slowest = hours;
      }
    }
    return fleets;
  }
}
