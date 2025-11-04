#include "../include/sand.h"
#include <stdlib.h>
#include <time.h>

#define CURRENT_TYPE SAND

void sand_init() {
    srand((unsigned)time(NULL));
}

int sand_getRandom(int min, int max) {
    return (rand() % (max - min) + 1) + min;
}

SDL_FRect sand_getDiagonalPoint(int x, int y, int diff) {
    SDL_FRect rightPoint;
    rightPoint.x = x;
    rightPoint.y = y;

    SDL_FRect leftPoint;
    leftPoint.x = x;
    leftPoint.y = y;

    int rightDiff = sand_getRandom(0, diff);
    int leftDiff  = sand_getRandom(0, diff);

    for (int i = 1; i <= rightDiff; i += 1) {
        if (!ph_validPoint(x + i, y + i)) {
            break;
        }
        int downType = ph_getType(x + i, y + i);
        if (downType == CURRENT_TYPE) {
            continue;
        }
        else if (ph_strongerThan(downType, CURRENT_TYPE)) {
            break;
        }

        rightPoint.x = x + i;
        rightPoint.y = y + i;
    }

    for (int i = 1; i <= leftDiff; i += 1) {
        if (!ph_validPoint(x - i, y + i)) {
            break;
        }
        int downType = ph_getType(x - i, y + i);
        if (downType == CURRENT_TYPE) {
            continue;
        }
        else if (ph_strongerThan(downType, CURRENT_TYPE)) {
            break;
        }
        leftPoint.x = x - i;
        leftPoint.y = y + i;
    }

    if (leftPoint.y > rightPoint.y) {
        return leftPoint;
    }
    else {
        return rightPoint;
    }

}

SDL_FRect sand_getPoint(int x, int y) {
    SDL_FRect point;
    point.x = x;
    point.y = y;
    for (int i = 1; i <= PARTICLE_SPEED; i += 1) {
        if (!ph_validPoint(x, y + i)) {
            break;
        }
        int downType = ph_getType(x, y + i);
        if (downType == CURRENT_TYPE) {
            continue;
        }
        else if (ph_strongerThan(downType, CURRENT_TYPE)) {
            break;
        }
        point.y = y + i;
    }

    if (point.y - y < PARTICLE_SPEED) {
        point = sand_getDiagonalPoint(point.x, point.y, PARTICLE_SPEED);
    }

    return point;
}


void sand_update(Particle* sandParticle) {
    SDL_FRect point = ph_getRect(SAND, sandParticle->sand.index);
    point = sand_getPoint(point.x, point.y);
    ph_setParticle(sandParticle, point.x, point.y);
}