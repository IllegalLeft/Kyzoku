/*
    Physics
*/

#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL_mixer.h"

#include "common.h"
#include "graphics.h"
#include "physics.h"
#include "sound.h"


void limit_vel(int x, int y)
{
    // limit x velocity
    if (player.vel_x > VELOCITY_LIMIT)
        player.vel_x = VELOCITY_LIMIT;
    if (player.vel_x < -VELOCITY_LIMIT)
        player.vel_x = -VELOCITY_LIMIT;

    // limit y velocity
    if (player.vel_y > VELOCITY_LIMIT)
        player.vel_y = VELOCITY_LIMIT;
    if (player.vel_y < -VELOCITY_LIMIT)
        player.vel_y = -VELOCITY_LIMIT;

    // prevent player from leaving the screen
    if((player.x + player.vel_x) > (SCREEN_WIDTH - PLAYER_WIDTH))
        player.vel_x = 0;
    if((player.x + player.vel_x) < 0)
        player.vel_x = 0;

    if((player.y + player.vel_y) > (SCREEN_HEIGHT - SCREEN_BAR_HEIGHT - PLAYER_HEIGHT))
        player.vel_y = 0;
    if((player.y + player.vel_y) < SCREEN_BAR_HEIGHT)
        player.vel_y = 0;
}

void apply_velocity(struct player_ship* player)
{
    // apply velocity
    player->x += player->vel_x;
    player->y += player->vel_y;
}

bool get_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    // NOTE: The 'top', 'bottom', etc are as you would think...
    //        top
    //      +------+
    // left |      | right
    //      |      |
    //      +------+
    //       bottom
    //
    int top1, bottom1, right1, left1;
    int top2, bottom2, right2, left2;

    // Sides of the objects
    top1 = y1;
    bottom1 = y1 + h1;
    left1 = x1;
    right1 = x1 + w1;

    top2 = y2;
    bottom2 = y2 + h2;
    left2 = x2;
    right2 = x2 + w2;

    // Check collisions (in reference to object 1)
    // top or bottom inside?
    if (((top2 >= top1) && (top2 <= bottom1)) || ((bottom2 >= top1) && (bottom2 <= bottom1)))
        // right or left side inside?
        if (((right2 >= left1) && (right2 <= right1)) || ((left2 >= left1) && (left2 <= right1)))
            return true;

    // if all else fails...
    return false;
}

bool check_collisions()
{
    bool collision;
    //int A_top, A_bottom, A_right, A_left;
    //int B_top, B_bottom, B_right, B_left;
    int i, j;

    // Player + Bullet (enemy)

    // Player & Enemy
	// Grab the player's positon once rather than everytime through loop (saves cycles)
	for (j = 0; j < MAX_ENEMIES; j++)
	{
		if(enemy[j].active == true)
        {
            collision = get_collision(player.x, player.y, player.w, player.h, enemy[j].x, enemy[j].y, enemy[j].w, enemy[j].h);

            if(collision == true)
			{
                Mix_PlayChannel(-1, snd_hit, 0);
				player.hp -= 10;
				if (player.hp <= 0)
                    return true; // True, the player is dead!
				player.score += enemy[j].value;
				enemy[j].active = false;
				collision = false; // Reset boolean
			}
		}
	}

    // Enemy & Bullets
    for (j = 0; j < MAX_ENEMIES; j++)
    {
        if (enemy[j].active == true)
        {
            // run through the bullets.
            for (i = 0; i < MAX_BULLETS; i++)
            {

                // Enemy top
                if (bullet[i].shot == true)
                {
                    collision = get_collision(enemy[j].x, enemy[j].y, enemy[j].w, enemy[j].h, bullet[i].x, bullet[i].y, bullet[i].w, bullet[i].h);

                    if (collision == true)
                    {
                        // B O O M ! (collision happens)
                        Mix_PlayChannel(-1, snd_hit, 0);
                        player.score += enemy[j].value;
                        bullet[i].shot = false;
                        enemy[j].active = false;
                    }
                }
            }
        }
    }
    return false;
}

// Bullet Physics
int init_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        // set bullet data
        bullet[i].x = 0;
        bullet[i].y = 0;
        bullet[i].w = BULLET_HEIGHT;
        bullet[i].h = BULLET_WIDTH;
        bullet[i].speed = 4;
        bullet[i].vel_x = bullet[i].speed;
        bullet[i].vel_y = 0;
        bullet[i].shot = false;
        // Image
        bullet[i].image = load_img("gfx/bullet.png");
        if (bullet[i].image == (SDL_Surface*)1)
            return 1;
        // Colour key
        Uint32 colorkey = SDL_MapRGB(bullet[i].image->format, 0, 0, 0);
        SDL_SetColorKey(bullet[i].image, SDL_SRCCOLORKEY, colorkey);
    }

    return 0;
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
            // is it JUST shot?
            if ((bullet[i].x == 0) && (bullet[i].y == 0))
            {
                bullet[i].x = player.x + player.w - BULLET_WIDTH;
                bullet[i].y = player.y + (player.h - BULLET_HEIGHT)/2;
            }

            bullet[i].x += bullet[i].vel_x;
            bullet[i].y += bullet[i].vel_y;
        }
        else
        {
            bullet[i].x = 0;
            bullet[i].y = 0;
        }
    }
    reset_bullets();
}

// Enemy Physics
void init_enemies()
{
    int i;

    for(i = 0; i < MAX_ENEMIES; i++)
    {
        // Data
        enemy[i].h = 0;
        enemy[i].w = 0;
        enemy[i].x = 0;
        enemy[i].y = 0;
        enemy[i].active = false;
        enemy[i].vel_x = 0;
        enemy[i].vel_y = 0;
        // Image
        enemy[i].tile = 3;
    }
}

void wave_spawn(int type, int formation, int amount)
{
    int x = SCREEN_WIDTH;
    int y = SCREEN_HEIGHT / 2;

    int i;
    for (i = 0; i < amount; i++)
    {
        switch(formation)
        {
            case 0:
                x += 32;
                break;
            case 1:
                y += 32;
                break;
            case 2:
                y += 32;
                x += 32;
                break;
            case 3:
                y -= 32;
                x += 32;
            default:
                x = x;
                y = y;
                break;
        }
        enemy_spawn(type, x, y);
    }
}

void enemy_spawn(int type, int x, int y)
{
    int i;
    for (i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemy[i].active == false)
        {
            // spawn enemy at random place on the right
            enemy[i].y = y;
            enemy[i].x = x;
            enemy[i].w = ENEMY_WIDTH;
            enemy[i].h = ENEMY_HEIGHT;
            enemy[i].active = true;
            enemy[i].vel_x = -3;
            enemy[i].vel_y = 0;
            enemy[i].value = 10;
            enemy[i].type = type;

            return; // Spawn one at a time
        }
    }
}

void enemy_move()
{
    int i;

    for (i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemy[i].active == true)
        {
            if (enemy[i].type == 0)     // STRAIGHT <--
            {
                // move enemies forward (to left)
                enemy[i].x += enemy[i].vel_x;
                enemy[i].y += enemy[i].vel_y;
            }
            if (enemy[i].type == 1)      // odd
            {
                enemy[i].x += enemy[i].vel_x;
                enemy[i].y += 1;
            }
            else if (enemy[i].type == 2)
            {
                enemy[i].x += enemy[i].vel_x;
                enemy[i].y -= 1;
            }
        }
        else
        {
            enemy[i].x = SCREEN_WIDTH;     //Offscreen, bottom, right
            enemy[i].y = SCREEN_HEIGHT;    //   "
        }

        // Catch off-screen bogies!
        if (enemy[i].x <= (-enemy[i].w))
            enemy[i].active = false;
    }
}
