/*
    Common

    - common typdefs, code, defines, etc.
*/

#include "screen.h"
#include <SDL/SDL.h>


#define MAX_BULLETS     10
#define MAX_ENEMIES     10
#define SHOT_WAIT       240

// bool type
typedef enum { false, true } bool;

// player
struct player_ship
{
    SDL_Surface* image;
    int h;
    int w;
    int x;
    int y;
    int vel_x;
    int vel_y;
    int last_shot;
	int hp;
} player;

// Enemy ship
struct enemy_ship
{
	SDL_Surface* image;
    int h;
    int w;
	int x;
	int y;
    int vel_x;
    int vel_y;
    bool active;
} enemy[MAX_ENEMIES];

//basic bullet structure
struct projectile
{
    SDL_Surface* image;
    int h;
    int w;
    int x;
    int y;
    int vel_x;
    int vel_y;
    int speed;
    bool shot;
} bullet[MAX_BULLETS];