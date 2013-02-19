/*
    Physics
*/

#include "common.h"

void moveship(int x, int y)
{
    player.vel_x = x * 4;

    //limit velocity
    if (player.vel_x > 4)
        player.vel_x = 4;
    if (player.vel_x < -4)
        player.vel_x = -4;

    player.vel_y = y * 4;

        //limit velocity
    if (player.vel_y > 4)
        player.vel_y = 4;
    if (player.vel_y < -4)
        player.vel_y = -4;

    if((player.x + player.vel_x) > (SCREEN_WIDTH - 30))
        player.vel_x = 0;
    if((player.x + player.vel_x) < 0)
        player.vel_x = 0;

    if((player.y + player.vel_y) > (SCREEN_HEIGHT - 30))
        player.vel_y = 0;
    if((player.y + player.vel_y) < 0)
        player.vel_y = 0;
}
