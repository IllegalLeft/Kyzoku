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
    player.x = (SCREEN_WIDTH - 30) / 2;
    player.y = (SCREEN_HEIGHT - 30) / 2;
    player.vel_x = 0;
    player.vel_y = 0;

    // set background data
    background.x = 0;
    background.y = 0;

    // the images
    player.image = load_img("ship.bmp");
    SDL_Surface* sector_img = load_img("sky.bmp");
    bullet.image = load_img("bullet.bmp");


    bool quit = false;

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

    SDL_Surface* screen = init_screen();

    // Colour keying
    Uint32 colorkey = SDL_MapRGB(player.image->format,0,0,0);
    SDL_SetColorKey(player.image,SDL_SRCCOLORKEY,colorkey);

    /// GAME LOOP
    while(quit == false)
    {

        /// Events
        quit = events();

        apply_velocity(&player);

        // apply background scrolling
        background.x -= 1;
        if(background.x < -SCREEN_WIDTH)
            background.x = 0;

        // slow player velocity
        if (player.vel_x > 0)
            player.vel_x /= 2;
        else player.vel_x = 0;
        if (player.vel_x < 0)
            player.vel_x /= 2;
        else player.vel_x = 0;

        if (player.vel_y > 0)
            player.vel_y /= 2;
        else player.vel_y = 0;
        if (player.vel_y < 0)
            player.vel_y /= 2;
        else player.vel_y = 0;

        /// Drawing
        // Apply image to screen
        apply_surface(background.x, background.y, sector_img, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector_img, screen);
        apply_surface(player.x, player.y, player.image, screen);

        // update screen
        SDL_Flip(screen);
    }

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(player.image);
    SDL_FreeSurface(bullet.image);

    // Quit SDL
    SDL_Quit();

    return 0;
}
