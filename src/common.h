/*
    Common

    - common typdefs, code, defines, etc.
*/

#include "screen.h"
#include <SDL/SDL.h>

#define MAX_BULLETS     10
#define SHOT_WAIT       120

// bool type
typedef enum { false, true } bool;

// player
struct player_ship
{
    SDL_Surface* image;
    int x;
    int y;
    int vel_x;
    int vel_y;
    int last_shot;
} player;

// Enemy ship
struct enemy_ship
{
	SDL_Surface* image;
	int x;
	int y;
} enemy;

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
} bullet[MAX_BULLETS];
