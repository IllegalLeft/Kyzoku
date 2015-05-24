/*
    Physics
*/

#define VELOCITY_LIMIT      200
#define PLAYER_ACCEL        2


void limit_vel(int x, int y);
void apply_velocity(struct player_ship* player);
bool get_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
bool check_collisions();

// Bullet Physics
int init_bullets();
void player_shoot();
void reset_bullets();
void move_bullets();

// Enemy Physics
void init_enemies();
void enemy_spawn(int type);
void enemy_move();
