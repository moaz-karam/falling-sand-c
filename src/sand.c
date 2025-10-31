#include "../include/sand.h"
#include <stdlib.h>


void sand_checkDown(Particle* sandParticle) {
    
}


void sand_update(Particle* sandParticle) {
    SDL_FPoint point;
    ph_getPoint(SAND, sandParticle->sand.index, &point);
    if (ph_validPoint(point.x, point.y + 3)) {
        ph_setParticle(sandParticle, point.x, point.y + 3);       
    }
}