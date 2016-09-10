/*
    Common

    - common typdefs, code, defines, etc.
*/

#include <stdbool.h>
#include <SDL/SDL.h>

#include "graphics.h"
#include "screen.h"

//debug stuff
#define DEBUG
#ifdef DEBUG
#define DEBUG_HITBOXES
//#define DEBUG_SPRITEBOXES
#endif


#define MAX_BULLETS     30
#define MAX_ENEMIES     20
#define MAX_ITEMS       20

#define ENEMY_SPAWNTIME 3000 //ms
#define SHOT_WAIT       260 //ms

// Hit-box Dimensions
// Player
#define PLAYER_HITX     0
#define PLAYER_HITY     10
#define PLAYER_WIDTH    28
#define PLAYER_HEIGHT   13
// Enemy
#define ENEMY1_HITX     9
#define ENEMY1_HITY     3
#define ENEMY1_WIDTH    16
#define ENEMY1_HEIGHT   27
#define ENEMY2_HITX     5
#define ENEMY2_HITY     9
#define ENEMY2_WIDTH    26
#define ENEMY2_HEIGHT   13
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

// item drop
struct item_drop
{
    int x;
    int y;
    bool active;
    short type;
} item[MAX_ITEMS];
