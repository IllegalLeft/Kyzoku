/*
    Graphics
*/

#include "SDL/SDL.h"
#include "common.h"

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

SDL_Surface* load_img(char* filename)
{
    SDL_Surface* img = SDL_LoadBMP(filename);

    return img;
}

SDL_Surface* init_screen()
{
    // screen surface
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Kyzoku",NULL);

    return screen;
}
