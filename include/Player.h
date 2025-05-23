#pragma once
#include "SDL.h"
#include "Vector.h"
#include "Entity.h"
#include "Weapon.h"
#include "EventManager.h"
#include "MessageManager.h"
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
    float skillpoints, energy, mana, maxEnergy, maxMana, currentXP;
    PlayerState playerState;
    Timer dashTimer, regenerateTimer;
    bool canDash;

public:
    Player();
    Player(SDL_Renderer *renderer);
    PlayerState getPlayerState();
    float getDamage();
    int getSkillPoints();
    float getEnergy();
    float getMaxEnergy();
    float getMana();
    float getMaxMana();
    void addXP(float xp);
    bool isAttacking(EventManager *EventManager);
    void handleDash();
    void processEvents(EventManager *eventManager);
    bool weaponInRange(SDL_Renderer *renderer, SDL_FRect *rect);
    void update(EventManager *eventManager, MessageManager *msgManager);
    void move(SDL_Renderer *renderer, Camera camera, EventManager *eventManager, vector<vector<Tile>> tiles, double timeStep);
};
