// Include SDL functions and data types
#include "SDL/SDL.h"
#include "common.h"

//background data
struct background_data
{
    int x; // Change these to double/float to allow smaller scrolling increments?
    int y;
};
struct background_data background;

int main(int argc, char* args[])
{

    // set player data
    player.x = 0;
    player.y = 0;
    player.vel_x = 0;
    player.vel_y = 0;

    // set background data
    background.x = 0;
    background.y = 0;

    // the images
    SDL_Surface* ship_img = load_img("ship.bmp");
    SDL_Surface* sector_img = load_img("sky.bmp");

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
        apply_surface(background.x, background.y, sector_img, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector_img, screen);
        apply_surface(player.x, player.y, ship_img, screen);

        // Update Screen
        SDL_Flip(screen);

        // events
        quit = events();

        // apply velocity
        player.x += player.vel_x;
        player.y += player.vel_y;

        // apply background scrolling
        background.x -= 1;
        if(background.x < -SCREEN_WIDTH)
            background.x = 0;

        // slow velocity
        if (player.vel_x > 0)
            player.vel_x /= 2;
        if (player.vel_x < 0)
            player.vel_x /= 2;

        if (player.vel_y > 0)
            player.vel_y /= 2;
        if (player.vel_y < 0)
            player.vel_y /= 2;
    }

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(ship_img);

    // Quit SDL
    SDL_Quit();

    return 0;
}
