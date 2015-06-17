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

// Bullet Drawing
void draw_bullets(SDL_Surface* screen)
{
    int i;
    for (i = 0; i < MAX_BULLETS;i++)
    {
        if (bullet[i].shot == true)
            apply_surface(bullet[i].x, bullet[i].y, bullet[i].image, screen);
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
    int i;
    for (i = 0; i < MAX_ENEMIES; i++)
        draw_sprite(enemy[i].x, enemy[i].y, enemy[i].tile, screen);
}


// Text Drawing
void text(char* message, int xcoord, int ycoord, SDL_Surface* screen)
{
	SDL_Color font_colour = {255, 0, 0};
	TTF_Font* font = TTF_OpenFont(FONT_FACE, FONT_SIZE);

	SDL_Surface* text = TTF_RenderText_Solid(font, message, font_colour);

	apply_surface(xcoord, ycoord, text, screen);

	SDL_FreeSurface(text);
	TTF_CloseFont(font);
}
