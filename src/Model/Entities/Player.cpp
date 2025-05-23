#include <Player.h>

Player::Player()
{
}

Player::Player(SDL_Renderer *renderer) : Entity()
{
    Animation *W, *S, *A, *D, *WA, *WD, *SA, *SD;
    title = "Warrior";
    entityType = PLAYER;
    playerState = IDLE;

    W = new Animation(renderer, "Assets/Entities/Player/W", 2, 0.25);
    S = new Animation(renderer, "Assets/Entities/Player/S", 2, 0.25);
    A = new Animation(renderer, "Assets/Entities/Player/A", 2, 0.25);
    D = new Animation(renderer, "Assets/Entities/Player/D", 2, 0.25);
    WA = new Animation(renderer, "Assets/Entities/Player/WA", 2, 0.25);
    WD = new Animation(renderer, "Assets/Entities/Player/WD", 2, 0.25);
    SA = new Animation(renderer, "Assets/Entities/Player/SA", 2, 0.25);
    SD = new Animation(renderer, "Assets/Entities/Player/SD", 2, 0.25);
    entity = {W, S, A, D, WA, WD, SA, SD};
    currentEntity = entity[1];

    width = currentEntity->getWidth();
    height = currentEntity->getHeight();
    playerState = IDLE;
    direction = Utilities::up;
    acceleration = 1;
    maxVelocity = 40;
    canDash = true;

    health = 100;
    maxHealth = 100;
    healthBar = Healthbar(renderer, health, maxHealth);

    energy = 100;
    maxEnergy = 100;

    mana = 100;
    maxMana = 100;

    skillpoints = 0;

    weapon = Axe(25, 0.1);

    regenerateTimer.start();
}

PlayerState Player::getPlayerState()
{
    return playerState;
}

float Player::getDamage()
{
    return weapon.getDamage();
}

int Player::getSkillPoints()
{
    return skillpoints;
}

float Player::getEnergy()
{
    return energy;
}

float Player::getMaxEnergy()
{
    return maxEnergy;
}

float Player::getMana()
{
    return mana;
}

float Player::getMaxMana()
{
    return maxMana;
}

void Player::addXP(float xp)
{
    currentXP += xp;
}

bool Player::isAttacking(EventManager *eventManager)
{
    if (eventManager->isLeftClick() && !weapon.isReloading() && energy >= 10)
    {
        energy -= 10;
        weapon.attack();
        return true;
    }
    return false;
}

void Player::handleDash()
{
    if (playerState == DASHING)
    {
        acceleration = 50;
        maxVelocity = 5000;

        if (dashTimer.getTicks() / 1000 >= 0.1)
        {
            playerState = IDLE;
            dashTimer.reset();
            canDash = false;
            acceleration = 1;
            maxVelocity = 20;
        }
    }
}

void Player::processEvents(EventManager *eventManager)
{
    weapon.handleAttacks();
    handleDash();

    if (playerState == DASHING)
    {
        return;
    }

    playerState = IDLE;
    currentEntity->startAnimation();

    if (eventManager->checkHoldKeyEvent(W))
    {
        playerState = UP;
        direction = Utilities::up;
    }
    else if (eventManager->checkHoldKeyEvent(S))
    {
        playerState = DOWN;
        direction = Utilities::down;
    }

    if (eventManager->checkHoldKeyEvent(D))
    {
        playerState = RIGHT;
        direction = Utilities::right;
        if (eventManager->checkHoldKeyEvent(W))
        {
            playerState = UPRIGHT;
            direction = Utilities::upRight;
        }
        else if (eventManager->checkHoldKeyEvent(S))
        {
            playerState = DOWNRIGHT;
            direction = Utilities::downRight;
        }
    }
    else if (eventManager->checkHoldKeyEvent(A))
    {
        playerState = LEFT;
        direction = Utilities::left;
        if (eventManager->checkHoldKeyEvent(W))
        {
            playerState = UPLEFT;
            direction = Utilities::upLeft;
        }
        else if (eventManager->checkHoldKeyEvent(S))
        {
            playerState = DOWNLEFT;
            direction = Utilities::downLeft;
        }
    }

    if (eventManager->checkPressKeyEvent(SPACE) && canDash && energy >= 40)
    {
        energy -= 40;
        dashTimer.start();
        playerState = DASHING;
    }
}

bool Player::weaponInRange(SDL_Renderer *renderer, SDL_FRect *rect)
{
    return weapon.inRange(renderer, rect);
}

void Player::update(EventManager *eventManager, MessageManager *msgManager)
{
    processEvents(eventManager);

    if (regenerateTimer.getTicks() / 1000 > 0.5)
    {
        energy += (5);
        regenerateTimer.start();
    }

    energy = (energy < maxEnergy) ? energy : maxEnergy;
    if (currentXP >= (100 * pow(level, 1.5)))
    {
        health = maxHealth;
        level += 1;
        skillpoints += 3;
        currentXP -= (100 * pow(level, 1.5));
        healthBar.setHealth(health, maxHealth);
        msgManager->levelUp();
    }
}

void Player::move(SDL_Renderer *renderer, Camera camera, EventManager *eventManager, vector<vector<Tile>> tiles, double timeStep)
{
    if (playerState != IDLE)
    {
        velocity += acceleration;
        velocity = (velocity >= maxVelocity) ? maxVelocity : velocity;
    }
    else if (playerState == IDLE)
    {
        velocity = 0;
    }

    prevPosition = position;
    position += direction.normalize() * velocity * timeStep;
    aimDirection = (eventManager->getMousePos() - (getPos() - camera.getOffset())).normalize();
    setEntityDirection();
    checkEdge(tiles, timeStep);

    rect = {position.x - camera.getX(), position.y - camera.getY(), width, height};
}
