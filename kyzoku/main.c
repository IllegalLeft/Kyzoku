// Include SDL functions and data types
#include "SDL/SDL.h"
#include "common.h"

int main(int argc, char* args[])
{
    // the images
    SDL_Surface* ship_img = NULL;
    SDL_Surface* sector_img = NULL;
    SDL_Surface* screen = NULL;

    // player data
    struct player_data
    {
        int x;
        int y;
    };

    struct player_data player;
    player.x = 100;
    player.y = 100;

    bool quit = false;



    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    init_screen(&screen);

    // Load images
    ship_img = SDL_LoadBMP("test.bmp");
    sector_img = SDL_LoadBMP("sector1.bmp");

    //Colour keying
    Uint32 colorkey = SDL_MapRGB(ship_img->format,0,0,0);
    SDL_SetColorKey(ship_img,SDL_SRCCOLORKEY,colorkey);

    /// GAME LOOP
    while(quit == false)
    {
        // Apply image to screen
        apply_surface(0,0, sector_img, screen);
        apply_surface(player.x, player.y, ship_img, screen);

        // Update Screen
        SDL_Flip(screen);

        quit = events();
    }

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(ship_img);

    // Quit SDL
    SDL_Quit();

    return 0;
}
