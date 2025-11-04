#ifndef SAND_HANDLER
#define SAND_HANDLER

#include "./particle_handler.h"

void sh_init();
void sh_end();

void sh_pushSand(Particle* sandParticle, int x, int y);
void sh_removeSand(int index);

SDL_FRect sh_getRect(int index);
Particle* sh_getParticle(int index);
void sh_setParticlePoint(Particle* sandParticle, int x, int y);
int sh_getSandNumber();
SDL_FRect* sh_getRects();



#endif