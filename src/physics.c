/*
    Physics
*/

#include "common.h"
#include <stdio.h>

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

/// BULLET PHYSICS
void init_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        // set bullet data
        bullet[i].x = player.x;
        bullet[i].y = player.y;
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

    if (!(next < 0))
    {
        bullet[next].shot = true;
        return 0;
    }
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
