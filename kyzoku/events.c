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
        }
    }
}
