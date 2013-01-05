// Include SDL functions and data types
#include "SDL/SDL.h"
#include "common.h"

// player data
struct player_data
{
    int x;      // x ordinate of ship
    int y;      // y ordinate of ship
    int vel_x;  // x velocity of ship
    int vel_y;  // y velocity of ship
};
struct player_data player;

void moveship(int x, int y)
{
    player.vel_x = x * 4;

    //limit velocity
    if (player.vel_x > 4)
        player.vel_x = 4;
    if (player.vel_x < -4)
        player.vel_x = -4;

    player.vel_y = y * 4;

        //limit velocity
    if (player.vel_y > 4)
        player.vel_y = 4;
    if (player.vel_y < -4)
        player.vel_y = -4;
}

int main(int argc, char* args[])
{

    // set player data
    player.x = 0;
    player.y = 0;
    player.vel_x = 0;
    player.vel_y = 0;

    // the images
    SDL_Surface* ship_img = load_img("ship.bmp");
    SDL_Surface* sector_img = load_img("sector1.bmp");

    bool quit = false;

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    SDL_Surface* screen = init_screen();
    //SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    //Colour keying
    Uint32 colorkey = SDL_MapRGB(ship_img->format,0,0,0);
    SDL_SetColorKey(ship_img,SDL_SRCCOLORKEY,colorkey);

    /// GAME LOOP
    while(quit == false)
    {

        // Apply image to screen
        apply_surface(player.x,player.y, sector_img, screen);
        apply_surface(320, 240, ship_img, screen);

        // Update Screen
        SDL_Flip(screen);

        // events
        quit = events();
        // apply velocity
        player.x += player.vel_x;
        player.y += player.vel_y;


        // slow velocity
        if (player.vel_x > 0)
            player.vel_x -= 1;
        if (player.vel_x < 0)
            player.vel_x += 1;

        if (player.vel_y > 0)
            player.vel_y -= 1;
        if (player.vel_y < 0)
            player.vel_y += 1;
    }

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(ship_img);

    // Quit SDL
    SDL_Quit();

    return 0;
}
