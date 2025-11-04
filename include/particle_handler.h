#ifndef Sand_HANDLER_H
#define Sand_HANDLER_H

#include <SDL3/SDL.h>


#define  SAND     0
#define  REMOVE   1

#define PARTICLE_SPEED 6

#define RED 0
#define GREEN 1
#define BLUE 2

#define PARTICLES 0
#define POINTS 1

#define PARTICLE_DIMENSION 5

static int COLORS[][3] = {
    {195, 178, 128} // sand
};


typedef struct {
    Uint8 type;
    unsigned int index;
} Sand;

typedef union {
    Uint8 type;
    Sand sand;
} Particle;

void ph_init(int w, int h);
void ph_end();

void ph_update();

void ph_select(int s);
void ph_setInserting(int i);

void ph_setMouse(int x, int y);


Particle* ph_getParticle(int x, int y);

void ph_setParticle(Particle* particle, int x, int y);

SDL_FRect ph_getRect(int type, unsigned int index);

void ph_removeParticle(int x, int y);

int ph_validPoint(int x, int y);

int ph_getType(int x, int y);

int ph_strongerThan(int t1, int t2);


#include "./sand.h"
#include "./sand_handler.h"

#endif