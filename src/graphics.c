/*
    Graphics
*/

#include <stdio.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "common.h"
#include "graphics.h"


// General Drawing
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    // Make a temp rect to hold the offsets
    SDL_Rect offset;

    // Set the offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

void draw_sprite(int x, int y, int tile, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_Rect sprite;
    sprite.w = SPRITE_WIDTH;
    sprite.h = SPRITE_HEIGHT;
    sprite.x = tile % 10 * SPRITE_WIDTH;
    sprite.y = tile / 10 * SPRITE_HEIGHT;

    SDL_BlitSurface(spritesheet, &sprite, destination, &offset);

#ifdef DEBUG_SPRITEBOXES
    offset.w = SPRITE_WIDTH;
    offset.h = SPRITE_HEIGHT;
    SDL_FillRect(destination, &offset, SDL_MapRGB(destination->format, 0x00, 0xFF, 0xFF));
#endif
}

void draw_item(int x, int y, int tile, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_Rect item;
    item.w = ITEM_WIDTH;
    item.h = ITEM_HEIGHT;
    item.x = tile % 10 * ITEM_WIDTH;
    item.y = tile / 10 * ITEM_HEIGHT;

    SDL_BlitSurface(itemsheet, &item, destination, &offset);

#ifdef DEBUG_HITBOXES
    offset.w = ITEM_WIDTH;
    offset.h = ITEM_HEIGHT;
    SDL_FillRect(destination, &offset, SDL_MapRGB(destination->format, 0xFF, 0x00, 0xFF));
#endif

}

SDL_Surface* load_img(char* filename)
{
    //SDL_Surface* img = SDL_LoadBMP(filename);
    SDL_Surface* img = IMG_Load(filename);
    if (img != NULL)
        return img;

    printf("Failed to load image %s\n\tError: %s\n", filename, IMG_GetError());
    return (SDL_Surface*)1;
}

SDL_Surface* init_screen()
{
    // icon
    SDL_Surface* icon = load_img("gfx/icon.png");
    SDL_WM_SetIcon(icon, NULL);

    // screen surface
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Kyzoku", NULL);

    return screen;
}

// Menu BG
void draw_menubg(SDL_Surface* screen, int array[20][20])
{
    int i, j;
    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
            draw_sprite(j*SPRITE_WIDTH, i*SPRITE_HEIGHT, array[i][j], screen);
    }
}

// Bullet Drawing
void draw_bullets(SDL_Surface* screen)
{
#ifdef DEBUG_HITBOXES
    SDL_Rect hitbox;
#endif
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        if (bullet[i].shot == true)
        {
            apply_surface(bullet[i].x, bullet[i].y, bullet[i].image, screen);

#ifdef DEBUG_HITBOXES
            hitbox.x = bullet[i].x;
            hitbox.y = bullet[i].y;
            hitbox.w = BULLET_WIDTH;
            hitbox.h = BULLET_HEIGHT;
            SDL_FillRect(screen, &hitbox, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00));
#endif
        }
    }
}

void free_bullets()
{
    int i;
    for (i = 0; i < MAX_BULLETS; i++)
        SDL_FreeSurface(bullet[i].image);
}

// Enemy Drawing
void draw_enemies(SDL_Surface* screen)
{
#ifdef DEBUG_HITBOXES
    SDL_Rect hitbox;
#endif
    int i;
    for (i = 0; i < MAX_ENEMIES; i++)
    {
        draw_sprite(enemy[i].x, enemy[i].y, enemy[i].tile, screen);
#ifdef DEBUG_HITBOXES
        switch (enemy[i].type)
        {
            case 0:
                hitbox.x = enemy[i].x + ENEMY1_HITX;
                hitbox.y = enemy[i].y + ENEMY1_HITY;
                hitbox.w = ENEMY1_WIDTH;
                hitbox.h = ENEMY1_HEIGHT;
                break;
            case 1:
                hitbox.x = enemy[i].x + ENEMY2_HITX;
                hitbox.y = enemy[i].y + ENEMY2_HITY;
                hitbox.w = ENEMY2_WIDTH;
                hitbox.h = ENEMY2_HEIGHT;
                break;
            default:
                break;
        }
        
        SDL_FillRect(screen, &hitbox, SDL_MapRGB(screen->format,0xFF,0x00,0x00));
#endif
    }
}


// Text Drawing
void text(char* message, int xcoord, int ycoord, SDL_Surface* screen)
{
	SDL_Color font_colour = {25, 25, 25};
	TTF_Font* font = TTF_OpenFont(FONT_FACE, FONT_SIZE);

	SDL_Surface* text = TTF_RenderText_Solid(font, message, font_colour);

	apply_surface(xcoord, ycoord, text, screen);

	SDL_FreeSurface(text);
	TTF_CloseFont(font);
}

// Items
void draw_items(SDL_Surface* screen)
{
    int i;
    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (item[i].active == true)
            draw_item(item[i].x, item[i].y, item[i].type, screen);
    }
}
