#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include "../include/particle_handler.h"
#include "SDL3/SDL.h"
#include <SDL3/SDL_main.h>

#define SDL_HINT_SHUTDOWN_DBUS_ON_QUIT "SDL_SHUTDOWN_DBUS_ON_QUIT"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static const bool* keyState;
static SDL_Event event;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("falling-sand", "1.0", "com.falling-sand");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("couldn't initialize SDL, %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("falling-sand", 1920, 1080, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("couldn't create window/renderer, %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    ph_init(1920, 1080);

    keyState = SDL_GetKeyboardState(NULL);


    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION) {
        ph_setMouse(event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        ph_setInserting(1);
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        ph_setInserting(0);
    }

    if (keyState[SDL_SCANCODE_S]) {
        ph_select(SAND);
    }
    else if (keyState[SDL_SCANCODE_R]) {
        ph_select(REMOVE);
    }

    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {

    ph_update();

    // clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);


    // drawing sand particles
    SDL_SetRenderDrawColor(renderer, COLORS[SAND][RED], COLORS[SAND][GREEN], COLORS[SAND][BLUE], SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(renderer, (sh_getPoints()), sh_getSandNumber());


    // rendering to the screen
    SDL_RenderPresent(renderer);

    // SDL_Delay(50);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    printf("Total Particles: %i\n", sh_getSandNumber());
    ph_end();
}
