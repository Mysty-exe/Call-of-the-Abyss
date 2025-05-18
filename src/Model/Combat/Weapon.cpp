#include <Weapon.h>

Weapon::Weapon()
{
}

Weapon::Weapon(float damage, float delay)
{
    this->damage = damage;
    this->delay = delay;
    reloading = false;
}

float Weapon::getDamage()
{
    return damage;
}

float Weapon::getRange()
{
    return range;
}

bool Weapon::isReloading()
{
    return reloading;
}

void Weapon::attack()
{
    reloading = true;
}

void Weapon::handleAttacks()
{
    if (reloading)
    {
        if (!attackDelay.isStarted())
        {
            attackDelay.start();
        }

        if (attackDelay.getTicks() / 1000 > delay)
        {
            attackDelay.reset();
            reloading = false;
        }
    }
}

void Weapon::displayArea(SDL_Renderer *renderer)
{
    Vector pos = position;
    Vector dir = direction;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < angle; i += 2)
    {
        SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + (dir * range).x, pos.y + (dir * range).y);
        dir.rotate(2);
    }
}

void Weapon::setRange(Vector pos, Vector dir)
{
    position = pos;
    // dir = Utilities::getIsometricDirection(dir, true);
    dir.rotate(-(angle / 2));

    // this->direction = Utilities::getIsometricDirection(dir, true);
    this->direction = dir;
}

bool Weapon::inRange(SDL_Renderer *renderer, SDL_FRect *rect)
{
    Vector dir = direction.normalize();

    for (int i = 0; i < angle; i += 2)
    {
        Vector pos = position;
        float finalX = (position.x + (dir * range).x);
        float finalY = (position.y + (dir * range).y);
        if (SDL_IntersectFRectAndLine(rect, &pos.x, &pos.y, &finalX, &finalY))
        {
            return true;
        }
        dir.rotate(2);
    }

    return false;
}

Unarmed::Unarmed() : Weapon()
{
}

Unarmed::Unarmed(float damage, float delay) : Weapon(damage, delay)
{
}

Sword::Sword() : Weapon()
{
}

Sword::Sword(float damage, float delay) : Weapon(damage, delay)
{
    range = 250;
    angle = 75;
}

Axe::Axe() : Weapon()
{
}

Axe::Axe(float damage, float delay) : Weapon(damage, delay)
{
    range = 200;
    angle = 120;
}

Spear::Spear() : Weapon()
{
}

Spear::Spear(float damage, float delay) : Weapon(damage, delay)
{
    range = 300;
    angle = 45;
}

Dagger::Dagger() : Weapon()
{
}

Dagger::Dagger(float damage, float delay) : Weapon(damage, delay)
{
    range = 125;
    angle = 100;
}