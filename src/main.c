/*
    Main
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "common.h"
#include "events.h"
#include "graphics.h"
#include "physics.h"
#include "sound.h"


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

    int lastspawn = 0; // last time enemy was spawned
    int lasttitlerefresh = 0; // last time title was refreshed

    // Text data
    char score_str[] = "Score: \0\0\0\0\0\0\0\0\0\0";
    char health_str[] = "Health: \0\0\0";
    char title_str[] = "Kyzoku - \0\0\0\0\0";

    int i, j;

    // set player data
    player.x = (SCREEN_WIDTH - 32) / 2;
    player.y = (SCREEN_HEIGHT - 32) / 2;
    player.vel_x = 0;
    player.vel_y = 0;
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;
	player.hp = 100; // For now, may need tweaking as we go
	player.score = 0;
    player.subweapon = 1; 

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
    player.tile = 1;

    SDL_Surface* sector_img = load_img(BACKGROUND_IMAGE);
    SDL_Surface* sector = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH,
                                               SCREEN_HEIGHT, SCREEN_BPP, 0, 0,
                                               0, 0);
    // background is made of many 'sector_img's
    for (i = 0; i < 10; i++) // draw many bg tiles onto one surface
    {
        for (j = 0; j < 9; j++)
        {
            apply_surface(i * 64, (j*64) + SCREEN_BAR_HEIGHT, sector_img, sector);
        }
    }
    // Bullet img loaded in init_bullets()
    // enemy images loaded in init_enemies()

    // Colour keying
    int colorkey = SDL_MapRGB(spritesheet->format,0,0,0);
    SDL_SetColorKey(spritesheet, SDL_SRCCOLORKEY, colorkey);
    // enemy colour key set in init_enemies
    // bullet colour key set in init_bullets


    /// GAME LOOP
    // if the game needs to be played it will jump in here
    while (stopgame == false)
    {
        // Grab start of frame
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
        if (SDL_GetTicks() >= ENEMY_SPAWNTIME + lastspawn)
        {
            wave_spawn(rand() % 2, 4);
            lastspawn = SDL_GetTicks();
        }
        // title refresh
        if (SDL_GetTicks() >= TITLE_REFRESH + lasttitlerefresh)
        {
            // FPS in title
            sprintf(title_str, "Kyzoku - %d", frame_time);
            SDL_WM_SetCaption(title_str, NULL);
            lasttitlerefresh = SDL_GetTicks();
        }

        /// Drawing
        // background
        apply_surface(background.x, background.y, sector, screen);
        apply_surface(background.x + SCREEN_WIDTH, background.y, sector, screen);

        draw_sprite(player.x, player.y, player.tile, screen);
        draw_enemies(screen);
        draw_bullets(screen);

        // top and bottom bar
        draw_sprite(0, 0, 20, screen);
        draw_sprite(SPRITE_WIDTH*19, 0, 22, screen);
        draw_sprite(0, SPRITE_HEIGHT*19, 20, screen);
        draw_sprite(SPRITE_WIDTH*19, SPRITE_HEIGHT*19, 22, screen);
        for (i = 1; i < (SCREEN_WIDTH/SPRITE_WIDTH) - 1; i++)
        {
            draw_sprite(i * 32, 0, 21, screen);
            draw_sprite(i * 32, SPRITE_HEIGHT*19, 21, screen);
        }

        // Text drawing
        sprintf(health_str, "Health: %d", player.hp);
        sprintf(score_str, "Score: %ld", player.score);
        text(health_str, 40, SCREEN_HEIGHT - SCREEN_BAR_HEIGHT + 7, screen);
        text(score_str, 40, 7, screen);

        // update screen
        SDL_Flip(screen);

        frame_time = SDL_GetTicks() - frame_start;
        //sprintf(title_str, "Kyzoku - %d", frame_time);
        //SDL_WM_SetCaption(title_str, NULL);
        // wait the rest of the frame
        if (frame_time < (1000 / FPS_LIMIT))
            SDL_Delay(1000 / (FPS_LIMIT - frame_time));
    }

    // Free loaded images
    SDL_FreeSurface(sector_img);
    SDL_FreeSurface(sector);
    free_bullets();
    //free_enemies();

    // Gameover
    SDL_Surface* gameover = load_img("gfx/gameover.png");
    //blank screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
    //draw gameover image
    apply_surface((SCREEN_WIDTH - 328)/2, (SCREEN_HEIGHT - 40)/2, gameover, screen);
    SDL_Flip(screen);
    SDL_Delay(1000);

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

    // Start sound
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
        return 1;

    // Redirect stdout and stderr streams to console (SDL sends to files by default)
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

    SDL_Surface* screen = init_screen();

    // Screen stuff
    // text
    char* menustrA = "Start";
    char* menustrB = "Quit";
    int menu_array[20][20] =
    {
        {10,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,11},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,20,21,21,21,21,21,21,22,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,20,21,21,21,21,21,21,22,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {13,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,12},
    };

    // images
    SDL_Surface* title = load_img("gfx/title.png");
    spritesheet = load_img(SPRITESHEET);

    // sounds
    Mix_Volume(-1, 128/2);
    snd_hit = Mix_LoadWAV(SND_HIT);
    snd_shoot = Mix_LoadWAV(SND_SHOOT);

    int menu_status = 1; // currently running menu = 1
    Mix_PlayChannel(-1, snd_hit, 0);
    while (menu_status)
    {
        // Grab start of frame
        frame_start = SDL_GetTicks();

        menu_status = menu_events();

        if (menu_status == 2) // play
        {
            Mix_PlayChannel(-1, snd_shoot, 0);
            gameloop();
        }
        else if (menu_status == 1);
        else
            break;

        // draw menu
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
        draw_menubg(screen, menu_array);
        apply_surface(SCREEN_WIDTH/2 - 232/2, 100, title, screen);
        // Text drawing
        text(menustrA, SCREEN_WIDTH/2-50,  9*SPRITE_HEIGHT+6, screen);
        text(menustrB, SCREEN_WIDTH/2-39, 11*SPRITE_HEIGHT+6, screen);

        // update screen
        SDL_Flip(screen);

        frame_time = SDL_GetTicks() - frame_start;

        // wait the rest of the frame
        if (frame_time < (1000/ FPS_LIMIT))
            SDL_Delay(1000 / (FPS_LIMIT - frame_time));
    }

    SDL_FreeSurface(title);
    SDL_FreeSurface(spritesheet);

    // Quit SDL
	TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
