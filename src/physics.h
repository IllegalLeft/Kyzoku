/*
    Physics
*/

void limit_vel(int x, int y);
void apply_velocity(struct player_ship* player);
bool check_collisions();

// Bullet Physics
void init_bullets();
void player_shoot();
void reset_bullets();
void move_bullets();

// Enemy Physics
void init_enemies();
void enemy_spawn();
void enemy_move();
