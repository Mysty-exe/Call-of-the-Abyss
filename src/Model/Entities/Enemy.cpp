#include <Enemy.h>

Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Renderer *renderer)
{
    entityType = ENEMY;
    currentEntity = new Animation(renderer, "Assets/Entities/Enemies", 2.5, 0.1);
    width = currentEntity->getWidth();
    height = currentEntity->getHeight();
    acceleration = 1;
    maxVelocity = 20;
    knockback = Vector(0, 0);

    health = 100;
    maxHealth = 100;
    healthBar = Healthbar(renderer, health, maxHealth);

    weapon = Unarmed(25, 3);
}

EnemyState Enemy::getEnemyState()
{
    return enemyState;
}

void Enemy::dealDamage(float damage)
{
    health -= damage;
    health = (health < 0) ? 0 : health;
    healthBar.dealDamage(position + Vector(rand() % int(width), 0), damage);
    knockback = direction * -1;
    knockbackTimer.start();
}

float Enemy::getXP()
{
    return 50;
}

Vector Enemy::seperate(vector<Entity *> entities, Player *player, double timeStep)
{
    Vector steer;
    int total = 0;

    for (Entity *other : entities)
    {
        float d = getPos().distance(other->getPos());

        if ((other != this && d < 40.0f && other->getEntityType() != PLAYER))
        {
            Vector diff = getPos() - other->getPos();
            diff = diff.normalize();
            diff /= d;
            steer += diff;
            total++;
        }
    }

    if (total > 0)
    {
        steer /= (float)total;
    }

    if (steer.magnitude() > 0)
    {
        steer = steer.normalize();
    }

    return steer;
}

void Enemy::trackPlayer(vector<Entity *> entities, Player *player, Camera &camera, vector<vector<Tile>> tiles, double timeStep)
{
    weapon.handleAttacks();
    enemyState = (!SDL_HasIntersectionF(getRect(), player->getRect())) ? FOLLOWING : CLOSE;
    if (enemyState == FOLLOWING)
    {
        velocity += acceleration;
        velocity = (velocity >= maxVelocity) ? maxVelocity : velocity;
    }
    else if (enemyState == CLOSE)
    {
        velocity = 0;

        if (!weapon.isReloading())
        {
            player->dealDamage(weapon.getDamage());
            camera.startScreenShake();
            weapon.attack();
        }
    }

    Vector separationForce = seperate(entities, player, timeStep);
    Vector seekForce = (player->getPos() - getPos());
    Vector prevPosition = position;

    if (knockback.magnitude() == 0)
    {
        position += (Utilities::getIsometricDirection(separationForce) * 0.2) * maxVelocity * timeStep;
        position += (Utilities::getIsometricDirection(seekForce) * 1) * velocity * timeStep;
    }
    else
    {
        velocity = 0;
    }

    direction = prevPosition - position;
    position -= knockback;

    if (knockbackTimer.isStarted())
    {
        if (knockbackTimer.getTicks() / 1000 > 0.1)
        {
            knockbackTimer.reset();
            knockback = Vector(0, 0);
        }
    }

    checkEdge(tiles, timeStep);
    rect = {position.x - camera.getX(), position.y - camera.getY(), width, height};
}
