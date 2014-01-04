/*
    Graphics

    Sam Volk, 2013
*/

// General Drawing
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
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
