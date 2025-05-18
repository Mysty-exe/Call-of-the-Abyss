#pragma once
#include <SDL.h>
#include <Texture.h>
#include <Vector.h>
#include <Timer.h>
#include <Utilities.h>

class Weapon
{
protected:
    int level;
    Vector position, direction;
    float damage, range, delay, angle;
    Timer attackDelay;
    bool reloading;

public:
    Weapon();
    Weapon(float damage, float delay);
    float getDamage();
    float getRange();
    bool isReloading();
    void attack();
    void handleAttacks();
    void displayArea(SDL_Renderer *renderer);
    void setRange(Vector pos, Vector dir);
    bool inRange(SDL_Renderer *renderer, SDL_FRect *rect);
};

class Unarmed : public Weapon
{
protected:
public:
    Unarmed();
    Unarmed(float damage, float delay);
};

class Sword : public Weapon
{
private:
public:
    Sword();
    Sword(float damage, float delay);
};

class Axe : public Weapon
{
private:
public:
    Axe();
    Axe(float damage, float delay);
};

class Spear : public Weapon
{
private:
public:
    Spear();
    Spear(float damage, float delay);
};

class Dagger : public Weapon
{
private:
public:
    Dagger();
    Dagger(float damage, float delay);
};
