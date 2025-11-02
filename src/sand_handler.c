#include <stdlib.h>
#include "../include/sand_handler.h"

typedef struct {

    SDL_FPoint* sandPoints;
    Particle** sandParticles;

    int size;
    int length;

} SandHandler;

static SandHandler sandHandler;

void sh_init() {

    sandHandler.size = 0;
    sandHandler.length = 4;

    sandHandler.sandPoints = (SDL_FPoint*)malloc(sizeof(SDL_FPoint) * sandHandler.length);
    sandHandler.sandParticles = (Particle**)malloc(sizeof(Particle*) * sandHandler.length);

}

void sh_end() {

    free(sandHandler.sandPoints);
    
    for (int i = 0; i < sandHandler.size; i += 1) {
        free(sandHandler.sandParticles[i]);
    }

    free(sandHandler.sandParticles);

}

SDL_FPoint sh_getPoint(int index) {
    return sandHandler.sandPoints[index];
}

Particle* sh_getParticle(int index) {
    return sandHandler.sandParticles[index];
}

void sh_setParticlePoint(Particle* sandParticle, int x, int y) {
    sandHandler.sandPoints[sandParticle->sand.index].x = x;
    sandHandler.sandPoints[sandParticle->sand.index].y = y;
}

int sh_getSandNumber() {
    return sandHandler.size;
}

void sh_resizeUp() {
    sandHandler.length *= 2;

    sandHandler.sandParticles =
     (Particle**)realloc(sandHandler.sandParticles, sizeof(Particle*) * sandHandler.length);
    
     sandHandler.sandPoints =
      (SDL_FPoint*)realloc(sandHandler.sandPoints, sizeof(SDL_FPoint) * sandHandler.length);
}

void sh_pushSand(Particle* sandParticle, int x, int y) {
    
    if (sandHandler.size / sandHandler.length >= 1) {
        sh_resizeUp();
    }

    sandParticle->type = SAND;
    sandParticle->sand.index = sandHandler.size;

    sandHandler.sandParticles[sandHandler.size] = sandParticle;

    sandHandler.sandPoints[sandHandler.size].x = x;
    sandHandler.sandPoints[sandHandler.size].y = y;

    sandHandler.size += 1;
}

void sh_removeSand(int index) {
    Particle* temp = sandHandler.sandParticles[index];
    Particle* finalParticle = sandHandler.sandParticles[sandHandler.size - 1];

    finalParticle->sand.index = index;

    sandHandler.sandParticles[index] = finalParticle;
    sandHandler.sandPoints[index] = sandHandler.sandPoints[sandHandler.size - 1];

    free(temp);
    sandHandler.size -= 1;
}

SDL_FPoint* sh_getPoints() {
    return sandHandler.sandPoints;
}

