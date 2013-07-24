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
                break;
            default:
                break;
            }
        }
    }

    // Check Key states
    Uint8 *keystates = SDL_GetKeyState(NULL);

    if (keystates[SDLK_LSHIFT])
    {
        if (keystates[SDLK_UP] || keystates[SDLK_w])
            player.vel_y = -1;
        if (keystates[SDLK_DOWN] || keystates[SDLK_s])
            player.vel_y = 1;
        if (keystates[SDLK_LEFT] || keystates[SDLK_a])
            player.vel_x = -1;
        if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
            player.vel_x = 1;
    }
    else
    {
        if (keystates[SDLK_UP] || keystates[SDLK_w])
            player.vel_y = -2;
        if (keystates[SDLK_DOWN] || keystates[SDLK_s])
            player.vel_y = 2;
        if (keystates[SDLK_LEFT] || keystates[SDLK_a])
            player.vel_x = -2;
        if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
            player.vel_x = 2;
    }

    limit_vel(player.vel_x, player.vel_y);

    if ( ( (keystates[SDLK_j]) || keystates[SDLK_c]) && (SDL_GetTicks() > SHOT_WAIT + player.last_shot) )
    {
        player_shoot();
        player.last_shot = SDL_GetTicks();
    }

    return false;
}