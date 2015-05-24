/*
    Main
*/

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "common.h"
#include "events.h"
#include "graphics.h"
#include "physics.h"

// Background data
struct background_data
{
    int x; // Change these to double/float to allow smaller scrolling increments?
    int y;
};
struct background_data background;

int gameloop()
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    int stopgame = false;
    int frame_start, frame_time;

    int lastspawn = 0;

    // Text data
    char score_str[] = "Score: \0\0\0\0\0\0\0\0\0\0";
    char health_str[] = "Health: \0\0\0";
    char title_str[] = "Kyzoku - \0\0\0\0\0";

    // set player data
    player.x = (SCREEN_WIDTH - 32) / 2;
    player.y = (SCREEN_HEIGHT - 32) / 2;
    player.vel_x = 0;
    player.vel_y = 0;
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;
	player.hp = 100; // For now, may need tweaking as we go
	player.score = 0;
    player.subweapon = 0; // Subweapon will be added later

    // set background data
    background.x = 0;
    background.y = 0;


    // initialize entities
    if (init_bullets())
    {
        fprintf(stderr, "Bullets failed to initialize.\n");
        return 1;
    }
    init_enemies();

    // the images
    player.image = load_img("gfx/player.png");
    SDL_Surface* sector_img = load_img("gfx/background.png");
    SDL_Surface* sector = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 640, SCREEN_BPP, 0, 0, 0, 0);    // background is made of many 'sector_img's
    int i, j = 0;
    for (i = 0; i < 10; i++) // draw many bg tiles onto one surface
    {
        for (j = 0; j < 8; j++)
        {
            apply_surface(i * 64, j * 64, sector_img, sector);
        }
    }
    // Bullet img loaded in init_bullets()
    // enemy images loaded in init_enemies()

    // Colour keying
    int colorkey = SDL_MapRGB(player.image->format,0,0,0);
    SDL_SetColorKey(player.image, SDL_SRCCOLORKEY, colorkey);
    // enemy colour key set in init_enemies
    // bullet colour key set in init_bullets


    /// GAME LOOP
    // if the game needs to be played it will jump in here
    while (stopgame == false)
    {
        // Grab start of fram
        frame_start = SDL_GetTicks();

        /// Events
        stopgame = game_events();

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

        if (stopgame != true)
            stopgame = check_collisions();

        // Bullets
        move_bullets();

        // Enemies
        enemy_move();
        if (SDL_GetTicks() >= 500 + lastspawn)
        {
            enemy_spawn(0);
            lastspawn = SDL_GetTicks();

            // FPS in title
            sprintf(title_str, "Kyzoku - %d", frame_time);
            SDL_WM_SetCaption(title_str, NULL);
        }

        /// Drawing
        // Apply image to screen
        apply_surface(background.x, background.y, sector, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector, screen);
        apply_surface(player.x, player.y, player.image, screen);
        draw_enemies(screen);
        draw_bullets(screen);

        // Text drawing
        sprintf(health_str, "Health: %d     %dx %dy", player.hp, player.x, player.y);
        sprintf(score_str, "Score: %d", player.score);
        text(health_str, 15, 450, screen);
        text(score_str, 215, 0, screen);

        // update screen
        SDL_Flip(screen);

        frame_time = SDL_GetTicks() - frame_start;
        //sprintf(title_str, "Kyzoku - %d", frame_time);
        //SDL_WM_SetCaption(title_str, NULL);
        // wait the rest of the frame
        if (frame_time < (1000/ FPS_LIMIT))
            SDL_Delay(1000 / (FPS_LIMIT - frame_time));
    }

    // Free loaded images
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(sector);
    SDL_FreeSurface(player.image);
    free_bullets();
    free_enemies();

    return 0;
}

int main(int argc, char* argv[])
{
    // set random seed
    srand(time(NULL));

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    int frame_start, frame_time;

    // Start TTF lib
    if (TTF_Init() == -1)
		return 1;

    // Redirect stdout and stderr streams to console (SDL sends to files by default)
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

    SDL_Surface* screen = init_screen();

    char* menustrA = "J / C -- Start Game";
    char* menustrB = "  ESC -- Quit the game";

    int menu_status = 1; // currently running menu = 1
    while (menu_status)
    {
        // Grab start of fram
        frame_start = SDL_GetTicks();

        menu_status = menu_events();

        if (menu_status == 2)
            gameloop();
        else if (menu_status == 1);
        else
            break;

        // draw menu
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
        // Text drawing
        text(menustrA, SCREEN_WIDTH/4, SCREEN_HEIGHT/2-20, screen);
        text(menustrB, SCREEN_WIDTH/4, SCREEN_HEIGHT/2, screen);

        // update screen
        SDL_Flip(screen);

        frame_time = SDL_GetTicks() - frame_start;
        //sprintf(title_str, "Kyzoku - %d", frame_time);
        //SDL_WM_SetCaption(title_str, NULL);
        // wait the rest of the frame
        if (frame_time < (1000/ FPS_LIMIT))
            SDL_Delay(1000 / (FPS_LIMIT - frame_time));
    }


    // Quit SDL and TTF
	TTF_Quit();
    SDL_Quit();

    return 0;
}
