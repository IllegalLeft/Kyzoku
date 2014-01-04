/*
    Main
*/

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "common.h"
#include "graphics.h"
#include "physics.h"

// Background data
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
    player.x = (SCREEN_WIDTH - 32) / 2;
    player.y = (SCREEN_HEIGHT - 32) / 2;
    player.vel_x = 0;
    player.vel_y = 0;
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;
	player.hp = 100; // For now, may need tweaking as we go
	player.score = 0;

    init_bullets();
    init_enemies();

    int lastspawn = 0;

    // set background data
    background.x = 0;
    background.y = 0;

    // Text data
    char score_str[] = "Score: \0\0\0\0\0\0\0\0\0\0";
    char health_str[] = "Health: \0\0\0";
    char title_str[] = "Kyzoku - \0\0\0\0\0";

    // the images
    player.image = load_img("../gfx/player.png");
    //enemy.image = load_img("../gfx/enemy.png");
    SDL_Surface* sector_img = load_img("../gfx/background.png");
    // Bullet img loaded in init_bullets()

    bool quit = false;

    // Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    int frame_start, frame_time;

	if (TTF_Init() == -1)
		return 1;

    // Redirect stdout and stderr streams to console (SDL sends to files by default)
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

    SDL_Surface* screen = init_screen();

    // Colour keying
    int colorkey = SDL_MapRGB(player.image->format,0,0,0);
    SDL_SetColorKey(player.image, SDL_SRCCOLORKEY, colorkey);
    // enemy colour key set in init_enemies
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

        if (quit != true)
            quit = check_collisions();

        // Bullets
        move_bullets();

        // Enemies
        enemy_move();
        if (SDL_GetTicks() >= 500 + lastspawn)
        {
            enemy_spawn();
            lastspawn = SDL_GetTicks();

            // FPS in title
            sprintf(title_str, "Kyzoku - %d", frame_time);
            SDL_WM_SetCaption(title_str, NULL);
        }

        /// Drawing
        // Apply image to screen
        apply_surface(background.x, background.y, sector_img, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector_img, screen);
        apply_surface(player.x, player.y, player.image, screen);
        draw_enemies(screen);
        draw_bullets(screen);

		// Text drawing
		sprintf(health_str, "Health: %d", player.hp);
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

    // Free loaded image
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(player.image);
    free_bullets();

    // Quit SDL and TTF
    SDL_Quit();
	TTF_Quit();

    return 0;
}
