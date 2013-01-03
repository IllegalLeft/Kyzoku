// Include SDL functions and data types
#include "SDL/SDL.h"

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      32

// define bool type
typedef enum { false, true } bool;

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    // Make a temp rect to hold the offsets
    SDL_Rect offset;

    // Set the offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

int main(int argc, char* args[])
{
    // the images
    SDL_Surface* ship = NULL;
    SDL_Surface* sector = NULL;
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

    SDL_Event event;
    bool quit = false;

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    // Set up screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Kyzoku",NULL);

    // Load images
    ship = SDL_LoadBMP("test.bmp");
    sector = SDL_LoadBMP("sector1.bmp");

    while(quit == false)
    {
        // Apply image to screen
        apply_surface(0,0, sector, screen);
        apply_surface(player.x, player.y, ship, screen);

        // Update Screen
        SDL_Flip(screen);

        //Event stuff
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = true;
            }
        }
    }

    // Free loaded image
    SDL_FreeSurface(sector);
    SDL_FreeSurface(ship);

    // Quit SDL
    SDL_Quit();

    return 0;
}
