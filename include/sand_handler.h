#ifndef SAND_HANDLER
#define SAND_HANDLER

#include "./particle_handler.h"

void sh_init();
void sh_end();

void sh_pushSand(Particle* sandParticle, int x, int y);
void sh_removeSand(int index);

SDL_FPoint sh_getPoint(int index);
Particle* sh_getParticle(int index);
void sh_setParticlePoint(Particle* sandParticle, int x, int y);
int sh_getSandNumber();
SDL_FPoint* sh_getPoints();



#endif