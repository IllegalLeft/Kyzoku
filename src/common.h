/*
    Common

    - common typdefs, code, defines, etc.
*/

#include <stdbool.h>
#include <SDL/SDL.h>

#include "graphics.h"
#include "screen.h"


#define MAX_BULLETS     20
#define MAX_ENEMIES     20
#define ENEMY_SPAWNTIME 3000 //ms
#define SHOT_WAIT       240 //ms

// Hit-box Dimensions
// Player
#define PLAYER_WIDTH    33
#define PLAYER_HEIGHT   29
// Enemy
#define ENEMY_WIDTH     21
#define ENEMY_HEIGHT    31
// Bullet
#define BULLET_WIDTH    12
#define BULLET_HEIGHT   3


// player
struct player_ship
{
    short tile;
    int h;
    int w;
    int x;
    int y;
    int vel_x;
    int vel_y;
    int last_shot;
    int hp;
    long score;
    int subweapon;
    int ammo;
} player;

// Enemy ship
struct enemy_ship
{
    short tile;
    int h;
    int w;
    int x;
    int y;
    int vel_x;
    int vel_y;
    bool active;
    int value;
    int type;
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
