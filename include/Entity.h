#pragma once
#include "SDL.h"
#include "Animation.h"
#include "Camera.h"
#include "Vector.h"
#include "Tile.h"
#include "Weapon.h"
#include "Healthbar.h"
#include "Utilities.h"
#include "vector"

enum EntityType
{
    PLAYER,
    ENEMY
};

class Entity
{
protected:
    string title;
    int level;
    float velocity, acceleration, maxVelocity;
    Vector position, prevPosition, direction, aimDirection, gravity;
    float width, height, health, maxHealth;
    SDL_FRect rect;
    vector<Animation *> entity;
    Animation *currentEntity;

    EntityType entityType;
    int currentRow, currentCol;

    Healthbar healthBar;

    Weapon weapon;

public:
    Entity();
    string getTitle();
    int getLevel();
    static bool compareY(Entity *e1, Entity *e2);
    EntityType getEntityType();
    Vector getPos();
    void setPos(Vector pos);
    int getCurrentRow();
    int getCurrentCol();
    Vector getDirection();
    int getWidth();
    int getHeight();
    float getHealth();
    float getMaxHealth();
    SDL_FRect *getRect();
void setEntityDirection();
void display(SDL_Renderer *renderer, Camera camera, bool showHealthbar);
    virtual void move(vector<vector<Tile>> tiles, double timeStep);
    void checkEdge(vector<vector<Tile>> tiles, double timeStep);
    void dealDamage(float damage);
    void free();
};
