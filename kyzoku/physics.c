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

void apply_velocity(struct sprite *Sprite)
{
    // apply velocity
    Sprite->x += Sprite->vel_x;
    Sprite->y += Sprite->vel_y;
}
