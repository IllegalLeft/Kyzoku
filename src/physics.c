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
		if (enemy[j].active == true)
        {
            collision = get_collision(player.x, player.y, player.w, player.h, enemy[j].x, enemy[j].y, enemy[j].w, enemy[j].h);

            if (collision == true)
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
                        if (rand() % 10)
                            item_spawn(rand()%2, enemy[j].x+(enemy[j].w/2)-(ITEM_WIDTH/2), enemy[j].y+(enemy[j].h/2)-(ITEM_WIDTH/2));
                    }
                }
            }
        }
    }

    // Player & items
    for (j = 0; j < MAX_ITEMS; j++)
    {
        if (item[j].active == true)
        {
            collision = get_collision(player.x, player.y, player.w, player.h, item[j].x, item[j].y, ITEM_WIDTH-1, ITEM_HEIGHT-1);

            if (collision == true)
            {
                item[j].active = false;
                switch (item[j].type)
                {
                    case 0: // health
                        player.hp += 10;
                        if (player.hp > 100) player.hp = 100;
                        break;
                    case 1: // tri gun
                        player.ammo += 10;                        
                        break;
                    default:
                        break;
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
    {
        // FIRE
        bullet[next].shot = true;
        bullet[next].vel_x = 3;
        bullet[next].vel_y = 0;
    }
}

void player_shootsub()
{
    int next = -1;
    int freebullets[5] = {-1, -1, -1, -1, -1};

    // Find next bullet
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullet[i].shot == false)
        {
            freebullets[next] = i;
            next++;
            if (next > 5)
                break;
        }
    }

    switch (player.subweapon)
    {
        case 0: // fast shot
            bullet[freebullets[0]].shot = true;
            bullet[freebullets[0]].vel_x = 14;
            bullet[freebullets[0]].vel_y = 0;
            break;
        case 1: // trigun
            bullet[freebullets[0]].shot = true;
            bullet[freebullets[0]].vel_x = 6;
            bullet[freebullets[0]].vel_y = 0;
            bullet[freebullets[1]].shot = true;
            bullet[freebullets[1]].vel_x = 5;
            bullet[freebullets[1]].vel_y = 2;
            bullet[freebullets[2]].shot = true;
            bullet[freebullets[2]].vel_x = 5;
            bullet[freebullets[2]].vel_y = -2;
            break;
        default:
            break;
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
        enemy[i].h = 0;
        enemy[i].w = 0;
        enemy[i].x = 0;
        enemy[i].y = 0;
        enemy[i].active = false;
        enemy[i].vel_x = 0;
        enemy[i].vel_y = 0;
        enemy[i].tile = 0;
    }
}

void wave_spawn(int type, int amount)
{
    int x, y;
    // spawn start
    switch (type)
    {
        case 0: // regular
            x = SCREEN_WIDTH;
            y = SCREEN_HEIGHT / 2;
            break;
        case 1: // fast
            x = SCREEN_WIDTH;
            y = SCREEN_HEIGHT / 4;
            break;
        default:
            x = SCREEN_WIDTH;
            y = SCREEN_HEIGHT / 2;

    }

    int i;
    for (i = 0; i < amount; i++)
    {
        // formation is based on type
        switch(type)
        {
            case 0:
                x += 32;
                break;
            case 1:
                y += 64;
                x += 16;
                break;
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

            // type dependant values
            switch (type)
            {
                case 0: // regular dude
                    enemy[i].tile = REGDUDE_TILE;
                    break;
                case 1: // fast dude
                    enemy[i].vel_x = -6;
                    enemy[i].tile = FASTGUY_TILE;
                    break;
                default:
                    break;
            }

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
            // move enemies forward (to left)
            enemy[i].x += enemy[i].vel_x;
            enemy[i].y += enemy[i].vel_y;
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


// ITEMS
int init_items()
{
    int i;
    for (i = 0; i < MAX_ITEMS; i++)
    {
        item[i].x = 0;
        item[i].y = 0;
        item[i].active = false;
        item[i].type = 0;
    }

    return 0;
}

int item_spawn(short type, int x, int y)
{
    int i;
    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (item[i].active == false)
        {
            // spawn item 
            item[i].y = y;
            item[i].x = x;
            item[i].active = true;
            item[i].type = type;

            return 1; // Spawn one at a time
        }
    }

    return 0;
}
