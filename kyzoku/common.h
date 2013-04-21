/*
    Common

    - common typdefs, code, defines, etc.
*/

#include "screen.h"
#include <SDL/SDL.h>

//#define MAX_BULLETS     10

// bool type
typedef enum { false, true } bool;

// basic sprite structure
struct sprite
{
    SDL_Surface* image;
    int x;
    int y;
    int vel_x;
    int vel_y;
};
struct sprite player;
struct sprite bullet;
