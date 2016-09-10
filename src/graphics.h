/*
    Graphics

    Sam Volk, 2013
*/

#define TITLE_REFRESH       1000 //ms

// Images
#define BACKGROUND_IMAGE    "gfx/background.png"
#define PLAYERBULLET_IMAGE  "gfx/bullet.png"

#define SPRITESHEET         "gfx/sprites.png"
#define SPRITE_WIDTH        32
#define SPRITE_HEIGHT       SPRITE_WIDTH

#define ITEMSHEET           "gfx/items.png"
#define ITEM_WIDTH          15
#define ITEM_HEIGHT         ITEM_WIDTH

// Dimensions
// Bullet
#define BULLET_IMG_WIDTH    12
#define BULLET_IMG_HEIGHT   3

// Enemy tile lookup
#define FASTGUY_TILE        4
#define REGDUDE_TILE        3

// Font
#define FONT_FACE   "src/PressStart2P.ttf"
#define FONT_SIZE   20


SDL_Surface* spritesheet;
SDL_Surface* itemsheet;


// General Drawing
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void draw_sprite(int x, int y, int tile, SDL_Surface* destination);
void draw_item(int x, int y, int tile, SDL_Surface* destination);
SDL_Surface* load_img(char* filename);
SDL_Surface* init_screen();

void draw_menubg(SDL_Surface* screen, int array[20][20]);

// Bullet Drawing
void draw_bullets(SDL_Surface* screen);
void free_bullets();

// Enemy Drawing
void draw_enemies(SDL_Surface* screen);

// Text Drawing
void text(char* message, int xcoord, int ycoord, SDL_Surface* screen);

// Items
void draw_items(SDL_Surface* screen);
