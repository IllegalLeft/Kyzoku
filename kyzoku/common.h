/*
    Common

    - common typdefs, code, defines, etc.
*/

// Screen Definitions
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      32

// bool type
typedef enum { false, true } bool;

// player data
struct player_data
{
    int x;      // x ordinate of ship
    int y;      // y ordinate of ship
    int vel_x;  // x velocity of ship
    int vel_y;  // y velocity of ship
};
struct player_data player;
