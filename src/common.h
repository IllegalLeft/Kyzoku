/*
    Common

    - common typdefs, code, defines, etc.
*/

#include "screen.h"
#include <SDL/SDL.h>

#define MAX_BULLETS     10

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

//basic bullet structure
struct projectile
{
    SDL_Surface* image;
    int x;
    int y;
    int vel_x;
    int vel_y;
    int speed;
    bool shot;
};
struct projectile bullet[MAX_BULLETS];
