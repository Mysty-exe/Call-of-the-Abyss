#include <XP.h>

XP::XP(SDL_Renderer *renderer, Vector pos, float xpAmount)
{
    this->pos = pos;
    this->xpAmount = xpAmount;
    this->xp = Animation(renderer, "Assets/Items/XP", 1, 0.01);
    maxVel = 50;
    acc = 1;
    vel = 0;
}

Vector XP::getPos()
{
    return pos;
}

float XP::getXP()
{
    return xpAmount;
}

bool XP::isAbsorbed()
{
    return absorbed;
}

void XP::moveXP(Vector finalPos)
{
    vel += acc;
    vel = (vel < maxVel) ? vel : maxVel;
    pos += (finalPos - pos).normalize() * vel;

    if (pos.distance(finalPos) < 10)
    {
        absorbed = true;
    }
}

void XP::drawXP(SDL_Renderer *renderer, Vector offset)
{
    xp.setCoords(pos.x - xp.getWidth() / 2, pos.y - xp.getHeight() / 2);
    xp.render(renderer, offset);
}
