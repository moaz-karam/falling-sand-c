#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/particle_handler.h"


Particle** grid;
int width;
int height;

ArrayList* sandParticles[2];

static int selectedType;
static int inserting;
static int insertionRadius;
static int mouseX;
static int mouseY;


void ph_init(int w, int h) {
    grid = (Particle**) malloc(sizeof(Particle*) * w * h);

    sandParticles[PARTICLES] = ArrayList_create(sizeof(Particle*));
    sandParticles[POINTS] = ArrayList_create(sizeof(SDL_FPoint));

    width = w;
    height = h;

    inserting = 0;
    insertionRadius = 30;
    selectedType = SAND;
    mouseX = 0;
    mouseY = 0;

    sand_init();
}

void ph_end() {


    for (int i = 0; i < sandParticles[PARTICLES]->size; i += 1) {
        Particle* container;
        ArrayList_get(sandParticles[PARTICLES], i, &container);
        free(container);
    }

    free(grid);

    ArrayList_end(sandParticles[PARTICLES]);
    ArrayList_end(sandParticles[POINTS]);

}




void ph_select(int s) {
    if (s > REMOVE || s < SAND) {
        return;
    }
    selectedType = s;
}

void ph_setInserting(int i) {
    inserting = i;
}

void ph_setMouse(int x, int y) {
    mouseX = x;
    mouseY = y;
}




Particle* ph_createParticle() {
    Particle* temp = (Particle*)malloc(sizeof(Particle));

    if (selectedType == SAND) {

        temp->type = SAND;
        temp->sand.index = sandParticles[PARTICLES]->size;

    }

    return temp;
}

void ph_pushParticle(Particle* particle, SDL_FPoint* point) {
    switch (particle->type) {
        case SAND:
            ArrayList_push(sandParticles[PARTICLES], &particle);
            ArrayList_push(sandParticles[POINTS], point);
            break;
    }
}

Particle* ph_getParticle(int x, int y) {
    return grid[x + y * width];
}

void ph_getPoint(int type, unsigned int index, SDL_FPoint* point) {
    if (type == SAND) {
        ArrayList_get(sandParticles[POINTS], index, point);
    }
}

int ph_validPoint(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void ph_insertMany(int mx, int my) {
    for (float r = insertionRadius; r > 0; r -= 0.5) {
        for (float theta = 0; theta < 360; theta += 1) {
            int x = mx + r * cos(theta);
            int y = my + r * sin(theta);

            if (!ph_validPoint(x, y)) {
                continue;
            }

            else if (selectedType == REMOVE) {
                ph_removeParticle(x, y);
            }
            else if (ph_getParticle(x, y) == NULL) {
                Particle* particle = ph_createParticle();

                SDL_FPoint point;
                point.x = (float)x;
                point.y = (float)y;

                ph_pushParticle(particle, &point);
                grid[(int)(point.x) + (int)(point.y) * width] = particle;
            }

        }
    }
}


void ph_insert() {
    ph_insertMany(mouseX, mouseY);
}


ArrayList* ph_getSandPoints() {
    return sandParticles[POINTS];
}




void ph_setParticle(Particle* particle, float x, float y) {
    if (particle->type == SAND) {
        SDL_FPoint tempPoint;

        // remove particle from the old positions
        ArrayList_get(sandParticles[POINTS], particle->sand.index, &tempPoint);
        grid[(int)tempPoint.x + (int)tempPoint.y * width] = NULL;


        // set particle to the new positions
        grid[(int)x + (int)y * width] = particle;
        tempPoint.x = x;
        tempPoint.y = y;
        ArrayList_set(sandParticles[POINTS], particle->sand.index, &tempPoint);
    }
}


// called after removeParticle when the particle in arrayList != the particle in the grid
// only called in the ph_update function
void ph_removeParticleHelper(Particle* particle) {
    Particle* temp;
    void* removingAddress;
    if (particle->type == SAND) {

        // 1. set the final particle to the index of the passed particle
        // 2. over write the passed particle in the array by the last element
        // 3. delete the passed particle
        
        ArrayList_get(sandParticles[PARTICLES], sandParticles[PARTICLES]->size - 1, &temp);
        temp->sand.index = particle->sand.index;

        removingAddress = ArrayList_getAddressOfIndex(sandParticles[PARTICLES], particle->sand.index);
        ArrayList_pop(sandParticles[PARTICLES], removingAddress);

        removingAddress = ArrayList_getAddressOfIndex(sandParticles[POINTS], particle->sand.index);
        ArrayList_pop(sandParticles[POINTS], removingAddress);

        free(particle);
    }

}

// called to set a particle to be removed in the next ph_update call
void ph_removeParticle(int x, int y) {
    grid[x + y * width] = NULL;
}

int ph_getType(int x, int y) {
    Particle* temp = ph_getParticle(x, y);
    if (temp == NULL) {
        return -1;
    }
    return temp->type;
}

int ph_strongerThan(int t1, int t2) {
    return t1 > t2;
}


void ph_update() {
    if (inserting > 0) {
        ph_insert();
    }

    for (int i = 0; i < sandParticles[PARTICLES]->size; i += 1) {
        Particle* sandParticle;
        SDL_FPoint sandPoint;

        ArrayList_get(sandParticles[PARTICLES], i, &sandParticle);
        ArrayList_get(sandParticles[POINTS], i, &sandPoint);

        if (ph_getParticle(sandPoint.x, sandPoint.y) != sandParticle) {
            
            // replaces the final particle by the particle to be removed
            ph_removeParticleHelper(sandParticle);
            
            // updating the replaced particle
            i -= 1;

            continue;
        }

        sand_update(sandParticle);
    }
}