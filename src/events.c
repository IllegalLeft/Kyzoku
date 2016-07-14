/*
    Events
*/

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "common.h"
#include "graphics.h"
#include "physics.h"
#include "sound.h"

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

    // Movement
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
    // Booster frame?
    if (keystates[SDLK_RIGHT] || keystates[SDLK_d])
        player.tile = 2;
    else
        player.tile = 1;

    limit_vel(player.vel_x, player.vel_y);

    // Shooting
    if ( ( (keystates[SDLK_j]) || keystates[SDLK_c]) && (SDL_GetTicks() > SHOT_WAIT + player.last_shot) )
    {
        player_shoot();
        player.last_shot = SDL_GetTicks();
        Mix_PlayChannel(-1, snd_shoot, 0);
    }
    // sub weapon
    else if ((keystates[SDLK_k] || keystates[SDLK_x]) && (SDL_GetTicks() > SHOT_WAIT + player.last_shot) && (player.ammo>0))
    {
        player_shootsub();
        player.ammo -= 1;
        player.last_shot = SDL_GetTicks();
        Mix_PlayChannel(-1, snd_shoot, 0);
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

        // KEY EVENTS
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                rcode = 0;
                break;
            default:
                rcode = 1;
            }
            break;
        // MOUSE DOWN EVENTS
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.y < SCREEN_HEIGHT/2)
                rcode = 2;
            if (event.button.y > SCREEN_HEIGHT/2)
                rcode = 0;
            break;
        }
    }

    // Check Key states
    Uint8 *keystates = SDL_GetKeyState(NULL);

    if (keystates[SDLK_c] || keystates[SDLK_j])
        rcode = 2;

    return rcode; // default is 'KEEP ON MENU-ING'
}
