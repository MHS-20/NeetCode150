#include <stdlib.h>

typedef struct {
    int pos, speed;
} Car;

static int byPosDesc(const void *a, const void *b) {
    return ((const Car *)b)->pos - ((const Car *)a)->pos;
}

int carFleet(int target, int *position, int positionSize, int *speed, int speedSize) {
    Car *cars = malloc(positionSize * sizeof(Car));
    for (int i = 0; i < positionSize; i++)
        cars[i] = (Car){position[i], speed[i]};
    qsort(cars, positionSize, sizeof(Car), byPosDesc);

    int fleets = 0;
    double slowest = 0; // arrival time of the fleet ahead
    for (int i = 0; i < positionSize; i++) {
        double hours = (double)(target - cars[i].pos) / cars[i].speed;
        if (hours > slowest) {
            fleets++;
            slowest = hours;
        }
    }
    free(cars);
    return fleets;
}
