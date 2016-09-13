/*
    Physics
*/

#define VEL_LIMIT_FAST      4
#define VEL_LIMIT_SLOW      2
#define PLAYER_ACCEL        2

// bullet velocities
#define BULLET_NORM_VELX        6
#define BULLET_NORM_VELY        0
#define BULLET_FAST_VELX        14
#define BULLET_FAST_VELY        0



void limit_vel(int* x, int* y, int limit);
void apply_vel(int *x, int *y, int vel_x, int vel_y);
bool get_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
bool check_collisions();

// Bullet Physics
int init_bullets();
void player_shoot();
void player_shootsub();
void reset_bullets();
void move_bullets();

// Enemy Physics
void init_enemies();
void wave_spawn(int type, int amount);
void enemy_spawn(int type, int x, int y);
void enemy_move();

// Items
int init_items();
int item_spawn(short type, int x, int y);
