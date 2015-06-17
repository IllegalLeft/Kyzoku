/*
    Graphics

    Sam Volk, 2013
*/

#define TITLE_REFRESH       1000 //ms

// Images
#define SPRITESHEET         "gfx/sprites.png"
#define SPRITE_WIDTH        32
#define SPRITE_HEIGHT       SPRITE_WIDTH

#define PLAYER_SPRITESHEET  "gfx/player.png"
#define ENEMY_IMAGE         "gfx/enemy.png"
#define BACKGROUND_IMAGE    "gfx/background.png"
#define PLAYERBULLET_IMAGE  "gfx/bullet.png"

// Dimensions
// player
#define PLAYER_IMG_WIDTH    39
#define PLAYER_IMG_HEIGHT   29
// Enemy
#define ENEMY_IMG_WIDTH     21
#define ENEMY_IMG_HEIGHT    31
// Bullet
#define BULLET_IMG_WIDTH    12
#define BULLET_IMG_HEIGHT   3

// Font
#define FONT_FACE   "src/PressStart2P.ttf"
#define FONT_SIZE   20


SDL_Surface* spritesheet;


// General Drawing
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void draw_sprite(int x, int y, int tile, SDL_Surface* destination);
SDL_Surface* load_img(char* filename);
SDL_Surface* init_screen();

// Bullet Drawing
void draw_bullets(SDL_Surface* screen);
void free_bullets();

// Enemy Drawing
void draw_enemies(SDL_Surface* screen);
void free_enemies();

// Text Drawing
void text(char* message, int xcoord, int ycoord, SDL_Surface* screen);
