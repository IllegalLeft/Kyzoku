/*
    Events
*/

#include "SDL/SDL.h"

#include "common.h"
#include "physics.h"

bool game_events()
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
            player.vel_y -= PLAYER_ACCEL / 2;
        if (keystates[SDLK_DOWN] || keystates[SDLK_s])
            player.vel_y += PLAYER_ACCEL / 2;
        if (keystates[SDLK_LEFT] || keystates[SDLK_a])
            player.vel_x -= PLAYER_ACCEL / 2;
        if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
            player.vel_x += PLAYER_ACCEL / 2;
    }
    else
    {
        if (keystates[SDLK_UP] || keystates[SDLK_w])
            player.vel_y -= PLAYER_ACCEL;
        if (keystates[SDLK_DOWN] || keystates[SDLK_s])
            player.vel_y += PLAYER_ACCEL;
        if (keystates[SDLK_LEFT] || keystates[SDLK_a])
            player.vel_x -= PLAYER_ACCEL;
        if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
            player.vel_x += PLAYER_ACCEL;
    }

    limit_vel(player.vel_x, player.vel_y);

    if ( ( (keystates[SDLK_j]) || keystates[SDLK_c]) && (SDL_GetTicks() > SHOT_WAIT + player.last_shot) )
    {
        player_shoot();
        player.last_shot = SDL_GetTicks();
    }

    return false;
}

int menu_events()
{
    int rcode = 1; // return 1 by default
    // Return codes:
    // 0  exit menu (and the program)
    // 1  continue on menu
    // 2  play game

    SDL_Event event;

    //Event stuff
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            rcode = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                rcode = 0;
                break;
            default:
                break;
            }
        }
    }

    // Check Key states
    Uint8 *keystates = SDL_GetKeyState(NULL);

    if (keystates[SDLK_c] || keystates[SDLK_j])
        rcode = 2;

    return rcode; // default is 'KEEP ON MENU-ING'
}
