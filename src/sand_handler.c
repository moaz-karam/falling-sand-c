#include <stdlib.h>
#include <math.h>
#include "../include/sand_handler.h"

typedef struct {

    SDL_FRect* sandRects;
    Particle** sandParticles;

    int size;
    int length;

} SandHandler;

static SandHandler sandHandler;

void sh_init() {

    sandHandler.size = 0;
    sandHandler.length = 4;

    sandHandler.sandRects = (SDL_FRect*)malloc(sizeof(SDL_FRect) * sandHandler.length);
    sandHandler.sandParticles = (Particle**)malloc(sizeof(Particle*) * sandHandler.length);

}

void sh_end() {

    free(sandHandler.sandRects);
    
    for (int i = 0; i < sandHandler.size; i += 1) {
        free(sandHandler.sandParticles[i]);
    }

    free(sandHandler.sandParticles);

}

SDL_FRect sh_getRect(int index) {
    SDL_FRect temp;
    temp.x = (int)floor(sandHandler.sandRects[index].x / PARTICLE_DIMENSION);
    temp.y = (int)floor(sandHandler.sandRects[index].y / PARTICLE_DIMENSION);
    return temp;
}

Particle* sh_getParticle(int index) {
    return sandHandler.sandParticles[index];
}

void sh_setParticlePoint(Particle* sandParticle, int x, int y) {
    sandHandler.sandRects[sandParticle->sand.index].x = x * PARTICLE_DIMENSION;
    sandHandler.sandRects[sandParticle->sand.index].y = y * PARTICLE_DIMENSION;
}

int sh_getSandNumber() {
    return sandHandler.size;
}

void sh_resizeUp() {
    sandHandler.length *= 2;

    sandHandler.sandParticles =
     (Particle**)realloc(sandHandler.sandParticles, sizeof(Particle*) * sandHandler.length);
    
     sandHandler.sandRects =
      (SDL_FRect*)realloc(sandHandler.sandRects, sizeof(SDL_FRect) * sandHandler.length);
}

void sh_pushSand(Particle* sandParticle, int x, int y) {
    
    if (sandHandler.size / sandHandler.length >= 1) {
        sh_resizeUp();
    }

    sandParticle->type = SAND;
    sandParticle->sand.index = sandHandler.size;

    sandHandler.sandParticles[sandHandler.size] = sandParticle;

    sandHandler.sandRects[sandHandler.size].x = x * PARTICLE_DIMENSION;
    sandHandler.sandRects[sandHandler.size].y = y * PARTICLE_DIMENSION;


    sandHandler.sandRects[sandHandler.size].w = PARTICLE_DIMENSION;
    sandHandler.sandRects[sandHandler.size].h = PARTICLE_DIMENSION;

    

    sandHandler.size += 1;
}

void sh_removeSand(int index) {
    Particle* temp = sandHandler.sandParticles[index];
    Particle* finalParticle = sandHandler.sandParticles[sandHandler.size - 1];

    finalParticle->sand.index = index;

    sandHandler.sandParticles[index] = finalParticle;
    sandHandler.sandRects[index] = sandHandler.sandRects[sandHandler.size - 1];

    free(temp);
    sandHandler.size -= 1;
}

SDL_FRect* sh_getRects() {
    return sandHandler.sandRects;
}

