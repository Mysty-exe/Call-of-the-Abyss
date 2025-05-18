#pragma once
#include "SDL.h"
#include "Vector.h"
#include "Entity.h"
#include "Player.h"
#include "Weapon.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Tile.h"
#include "Timer.h"
#include "algorithm"

enum EnemyState
{
    FOLLOWING,
    CLOSE,
    SEPERATE
};

class Enemy : public Entity
{
private:
    Vector knockback;
    EnemyState enemyState;
    Timer showingHealthbar, knockbackTimer;

public:
    Enemy();
    Enemy(SDL_Renderer *renderer);
    EnemyState getEnemyState();
    void dealDamage(float damage);
    Vector seperate(vector<Entity *> entities, Player *player, double timeStep);
    void trackPlayer(vector<Entity *> entities, Player *player, Camera &camera, vector<vector<Tile>> tiles, double timeStep);
};
