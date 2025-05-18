#include <Player.h>

Player::Player()
{
}

Player::Player(SDL_Renderer *renderer) : Entity()
{
    title = "Warrior";
    entityType = PLAYER;
    playerState = IDLE;
    entity.loadFromFile(renderer, "Assets/Entities/player.png", 2.5);
    width = entity.getWidth();
    height = entity.getHeight();
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

int Player::getEnergy()
{
    return energy;
}

int Player::getMaxEnergy()
{
    return maxEnergy;
}

int Player::getMana()
{
    return mana;
}

int Player::getMaxMana()
{
    return maxMana;
}

bool Player::isAttacking(EventManager *eventManager)
{
    if (eventManager->isLeftClick() && !weapon.isReloading())
    {
        weapon.attack();
        return true;
    }
    return false;
}

void Player::handleDash()
{
    if (!canDash)
    {
        if (!dashTimer.isStarted())
        {
            dashTimer.start();
        }

        if (dashTimer.getTicks() / 1000 >= 3)
        {
            canDash = true;
        }
    }

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

    if (eventManager->checkPressKeyEvent(SPACE) && canDash)
    {
        dashTimer.start();
        playerState = DASHING;
    }
}

bool Player::weaponInRange(SDL_Renderer *renderer, SDL_FRect *rect)
{
    return weapon.inRange(renderer, rect);
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
    checkEdge(tiles, timeStep);

    rect = {position.x - camera.getX(), position.y - camera.getY(), width, height};
}
