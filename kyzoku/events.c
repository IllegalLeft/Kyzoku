/*
    Events
*/

#include "SDL/SDL.h"
#include "common.h"

bool events()
{
    SDL_Event event;
    Uint32 ticks = SDL_GetTicks();

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
        player.vel_y = -2;
    if (keystates[SDLK_DOWN])
        player.vel_y = 2;
    if (keystates[SDLK_LEFT])
        player.vel_x = -2;
    if (keystates[SDLK_RIGHT])
        player.vel_x = 2;

    limit_vel(player.vel_x, player.vel_y);

    if ((keystates[SDLK_SPACE]) && ((ticks % 120) <= 6))
        shoot();

    return false;
}
