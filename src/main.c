// Include SDL functions and data types
#include "SDL/SDL.h"
#include "common.h"
#include "gfx.h"
#include <stdlib.h>
#include <time.h>


//background data
struct background_data
{
    int x; // Change these to double/float to allow smaller scrolling increments?
    int y;
};
struct background_data background;

int main(int argc, char* argv[])
{

    srand(time(NULL));

    // set player data
    player.x = (SCREEN_WIDTH - 30) / 2;
    player.y = (SCREEN_HEIGHT - 30) / 2;
    player.vel_x = 0;
    player.vel_y = 0;
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;

    init_bullets();

    // set background data
    background.x = 0;
    background.y = 0;

    // the images
    player.image = load_img("../gfx/player.png");
    enemy.image = load_img("../gfx/enemy.png");
    SDL_Surface* sector_img = load_img("../gfx/sky.bmp");
    // Bullet img loaded in init_bullets()

    bool quit = false;

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    int frame_start, frame_time;

    // Redirect stdout and stderr streams to console (SDL sends to files by default)
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

    SDL_Surface* screen = init_screen();

    // Colour keying
    int colorkey = SDL_MapRGB(player.image->format,0,0,0);
    SDL_SetColorKey(player.image, SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(enemy.image, SDL_SRCCOLORKEY, colorkey);
    // bullet colour key set in init_bullets

    /// GAME LOOP
    while(quit == false)
    {
        // Grab start of fram
        frame_start = SDL_GetTicks();

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

        check_collisions();

        // Bullets
        move_bullets();

        // Enemies
        enemy_move();
        if (enemy.active != true)
            enemy_spawn();

        /// Drawing
        // Apply image to screen
        apply_surface(background.x, background.y, sector_img, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector_img, screen);
        apply_surface(player.x, player.y, player.image, screen);
        draw_enemies(screen);
        draw_bullets(screen);

        // update screen
        SDL_Flip(screen);

        frame_time = SDL_GetTicks() - frame_start;
        // wait the rest of the frame
        if (frame_time < (1000/ FPS_LIMIT))
            SDL_Delay(1000 / (FPS_LIMIT - frame_time));

        //int test = (FPS_LIMIT - frame_time)/1000;
        //printf("%d\n",test);

    }

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(player.image);
    free_bullets();

    // Quit SDL
    SDL_Quit();

    return 0;
}
