#ifndef Sand_HANDLER_H
#define Sand_HANDLER_H

#include <SDL3/SDL.h>

#include "./data_structures/dll/dll.h"
#include "./data_structures/array_list/array_list.h"

#define  SAND     0
#define  REMOVE   1

#define PARTICLE_SPEED 4

#define RED 0
#define GREEN 1
#define BLUE 2

#define PARTICLES 0
#define POINTS 1

static int COLORS[][3] = {
    {195, 178, 128} // sand
};


typedef struct {
    unsigned int type;
    unsigned int index;
} Sand;

typedef union {
    unsigned int type;
    Sand sand;
} Particle;

void ph_init(int w, int h);
void ph_end();

void ph_update();

void ph_select(int s);
void ph_setInserting(int i);

void ph_setMouse(int x, int y);


Particle* ph_getParticle(int x, int y);

void ph_setParticle(Particle* particle, float x, float y);

void ph_getPoint(int type, unsigned int index, SDL_FPoint* point);

void ph_removeParticle(int x, int y);

int ph_validPoint(int x, int y);

ArrayList* ph_getSandPoints();

#include "sand.h"

#endif