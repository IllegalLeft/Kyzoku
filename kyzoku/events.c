/*
    Events
*/

#include "SDL/SDL.h"
#include "common.h"

bool events()
{
    SDL_Event event;

    //Event stuff
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            return true;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return true;
            }
        }
    }

    // Check Key states
    Uint8 *keystates = SDL_GetKeyState(NULL);

    if (keystates[SDLK_UP])
        moveship(0,-1);
    if (keystates[SDLK_DOWN])
        moveship(0,1);
    if (keystates[SDLK_LEFT])
        moveship(-1,0);
    if (keystates[SDLK_RIGHT])
        moveship(1,0);

    //if (keystates[SDLK_SPACE])
        //shoot();

    return false;
}
