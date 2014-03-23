/*
    Common

    - common typdefs, code, defines, etc.
*/

#include <SDL/SDL.h>

#include "screen.h"


#define MAX_BULLETS     2
#define MAX_ENEMIES     10
#define SHOT_WAIT       240

// Dimensions
// Player
#define PLAYER_WIDTH    32
#define PLAYER_HEIGHT   24
// Enemy
#define ENEMY_WIDTH     32
#define ENEMY_HEIGHT    16
// Bullet
#define BULLET_WIDTH    5
#define BULLET_HEIGHT   5

//Physics
#define PLAYER_VEL_LIMIT 10


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
	int score;
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
    int value;
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
