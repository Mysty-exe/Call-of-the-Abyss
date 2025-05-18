#pragma once
#include "SDL.h"
#include "Vector.h"
#include "Entity.h"
#include "Weapon.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Tile.h"
#include "Timer.h"
#include "algorithm"

enum PlayerState
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPLEFT,
    UPRIGHT,
    DOWNLEFT,
    DOWNRIGHT,
    IDLE,
    DASHING
};

class Player : public Entity
{
private:
    int skillpoints, energy, mana, maxEnergy, maxMana;
    PlayerState playerState;
    Timer dashTimer;
    bool canDash;

public:
    Player();
    Player(SDL_Renderer *renderer);
    PlayerState getPlayerState();
    float getDamage();
    int getSkillPoints();
    int getEnergy();
    int getMaxEnergy();
    int getMana();
    int getMaxMana();
    bool isAttacking(EventManager *EventManager);
    void handleDash();
    void processEvents(EventManager *eventManager);
    bool weaponInRange(SDL_Renderer *renderer, SDL_FRect *rect);
    void move(SDL_Renderer *renderer, Camera camera, EventManager *eventManager, vector<vector<Tile>> tiles, double timeStep);
};
