/*
    Physics
*/

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"

void limit_vel(int x, int y)
{
    // speed
    player.vel_x = x * 1;
    player.vel_y = y * 1;

    // limit x velocity
    if (player.vel_x > 10)
        player.vel_x = 10;
    if (player.vel_x < -10)
        player.vel_x = -10;

    // limit y velocity
    if (player.vel_y > 10)
        player.vel_y = 10;
    if (player.vel_y < -10)
        player.vel_y = -10;

    //
    if((player.x + player.vel_x) > (SCREEN_WIDTH - 30))
        player.vel_x = 0;
    if((player.x + player.vel_x) < 0)
        player.vel_x = 0;

    if((player.y + player.vel_y) > (SCREEN_HEIGHT - 30))
        player.vel_y = 0;
    if((player.y + player.vel_y) < 0)
        player.vel_y = 0;

    //printf("vx:%d vy:%d\n",player.vel_x, player.vel_y);
}

void apply_velocity(struct player_ship* player)
{
    // apply velocity
    player->x += player->vel_x;
    player->y += player->vel_y;
}

void check_collisions()
{
    bool collision = true;
    int A_top, A_bottom, A_right, A_left;
    int B_top, B_bottom, B_right, B_left;
    int i;

    // Player + Bullet
    //// BLANK 4 NOW

    // ENEMY + Bullets
    //   A       B    
    A_top = enemy.y;
    A_bottom = enemy.y + enemy.h;
    A_left = enemy.x;
    A_right = enemy.x + enemy.w;

    // run through the bullets.
    for (i = 0; i < MAX_BULLETS; i++)
    {

        // Enemy top
        if (bullet[i].shot == true)
        {
            collision = true;

            B_top = bullet[i].y;
            B_bottom = bullet[i].y + bullet[i].h;
            B_left = bullet[i].x;
            B_right = bullet[i].x + bullet[i].w;

            if (A_top >= B_bottom)
                collision = false;
            // Enemy bottom
            if (A_bottom <= B_top)
                collision = false;
            // Enemy left
            if (A_left >= B_right)
                collision = false;
            // Enemy right
            if (A_right <= B_left)
                collision = false;
            

            if (collision == true)
            {
                bullet[i].shot = false;
                enemy.active = false;
            }
        }
    }
}

/// BULLET PHYSICS
void init_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        // set bullet data
        bullet[i].x = player.x;
        bullet[i].y = player.y;
        bullet[i].w = BULLET_HEIGHT;
        bullet[i].h = BULLET_WIDTH;
        bullet[i].speed = 4;
        bullet[i].vel_x = bullet[i].speed;
        bullet[i].vel_y = 0;
        bullet[i].shot = false;
        // Image
        bullet[i].image = load_img("../gfx/bullet.bmp");
        // Colour key
        Uint32 colorkey = SDL_MapRGB(bullet[i].image->format,0,0,0);
        SDL_SetColorKey(bullet[i].image, SDL_SRCCOLORKEY, colorkey);
    }
}

void player_shoot()
{
    int next = -1;

    // Find next bullet
    int i;
    for (i = 0; i < MAX_BULLETS; i++)
    {
        if (bullet[i].shot == false)
        {
            next = i;
            break;
        }
    }

    if (!(next < 0) )
        bullet[next].shot = true;
}

void reset_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        if (bullet[i].x > SCREEN_WIDTH)
            bullet[i].shot = false;
    }

}

void move_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        if (bullet[i].shot == true)
        {
            bullet[i].x += bullet[i].vel_x;
            bullet[i].y += bullet[i].vel_y;
        }
        else
        {
            bullet[i].x = player.x;
            bullet[i].y = player.y;
        }

    }
    reset_bullets();
}

// ENEMY PHYSICS
void enemy_spawn()
{
    // spawn enemy at random place on the right
    enemy.y = rand() % (SCREEN_HEIGHT - player.h); // Needs to be random soon enough...
    enemy.x = SCREEN_WIDTH; // Offscreen
    enemy.w = ENEMY_WIDTH;
    enemy.h = ENEMY_HEIGHT;
    enemy.active = true;
    enemy.vel_x = -1;
    enemy.vel_y = 0;
}

void enemy_move()
{
    if (enemy.active == true)
    {
        // move enemies forward (to left)
        enemy.x += enemy.vel_x;
        enemy.y += enemy.vel_y;
    }    
    else
    {
        enemy.x = SCREEN_WIDTH;     //Offscreen, bottom, right
        enemy.y = SCREEN_HEIGHT;    //   "
    }
}
