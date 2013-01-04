/*
    Graphics

*/

#include "SDL/SDL.h"


#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      32

// apply_surface
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    // Make a temp rect to hold the offsets
    SDL_Rect offset;

    // Set the offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

int init_screen(SDL_Surface** screen)
{
    // Set up screen
    *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Kyzoku",NULL);

    return 0;
}

void update(SDL_Surface* surf)
{
    SDL_Flip(surf);
}
