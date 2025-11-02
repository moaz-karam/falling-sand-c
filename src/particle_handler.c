#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/particle_handler.h"


Particle** grid;
int width;
int height;


static int selectedType;
static int inserting;
static int insertionRadius;
static int mouseX;
static int mouseY;


void ph_init(int w, int h) {
    grid = (Particle**) malloc(sizeof(Particle*) * w * h);

    width = w;
    height = h;

    inserting = 0;
    insertionRadius = 30;
    selectedType = SAND;
    mouseX = 0;
    mouseY = 0;

    sh_init();
    sand_init();
}

void ph_end() {

    free(grid);
    
    sh_end();
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

    return temp;
}


Particle* ph_getParticle(int x, int y) {
    return grid[x + y * width];
}

SDL_FPoint ph_getPoint(int type, unsigned int index) {
    if (type == SAND) {
        return sh_getPoint(index);
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
                
                sh_pushSand(particle, x, y);

                grid[x + y * width] = particle;
            }
        }
    }
}


void ph_insert() {
    ph_insertMany(mouseX, mouseY);
}



void ph_setParticle(Particle* particle, float x, float y) {
    if (particle->type == SAND) {
        SDL_FPoint tempPoint = sh_getPoint(particle->sand.index);

        // remove particle from the old positions
        grid[(int)tempPoint.x + (int)tempPoint.y * width] = NULL;


        // set particle to the new positions
        grid[(int)x + (int)y * width] = particle;
        sh_setParticlePoint(particle, x, y);
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

    for (int i = 0; i < sh_getSandNumber(); i += 1) {
        Particle* sandParticle = sh_getParticle(i);
        SDL_FPoint sandPoint = sh_getPoint(i);

        if (ph_getParticle(sandPoint.x, sandPoint.y) != sandParticle) {
            
            // replaces the final particle by the particle to be removed
            sh_removeSand(i);
            
            // updating the replaced particle
            i -= 1;

            continue;
        }

        sand_update(sandParticle);
    }
}