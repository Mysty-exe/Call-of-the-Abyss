#include <Healthbar.h>

Healthbar::Healthbar()
{
}

Healthbar::Healthbar(SDL_Renderer *renderer, float health, float maxHealth)
{
    this->renderer = renderer;
    this->health = health;
    this->maxHealth = maxHealth;

    font = TTF_OpenFont("Assets/Fonts/font.ttf", 16);
}

bool Healthbar::isDead()
{
    return health <= 0;
}

float Healthbar::getHealth()
{
    return health;
}

void Healthbar::dealDamage(Vector pos, float damage)
{
    Texture dmg;
    if (rand() % 10 == 0)
    {
        damage *= (1.5 + (rand() % 2));
        dmg.loadFromRenderedText(renderer, font, to_string(int(damage)), {201, 150, 8}, int(damage) / 25);
    }
    else
    {
        dmg.loadFromRenderedText(renderer, font, to_string(int(damage)), {201, 66, 32}, int(damage) / 25);
    }

    dmg.setCoords(pos + Vector(0, -(dmg.getHeight() + 5)));

    damageNumbers.push_back(make_pair(dmg, Timer()));
    damageNumbers[damageNumbers.size() - 1].second.start();
    this->health -= damage;

    this->health = (this->health < 0) ? 0 : this->health;
}

void Healthbar::displayDmgNumbers(Vector offset)
{
    for (pair<Texture, Timer> dmg : damageNumbers)
    {
        dmg.first.render(renderer, offset);
    }

    damageNumbers.erase(
        remove_if(damageNumbers.begin(), damageNumbers.end(),
                  [](pair<Texture, Timer> dmg)
                  { return dmg.second.getTicks() / 1000 > 0.5; }),
        damageNumbers.end());
}

void Healthbar::displayHealthbar(Vector pos, Vector size)
{
    float r, g;
    if (health / maxHealth > 0.5)
    {
        g = 255;
        r = 255 - (255 * ((health / maxHealth)));
    }
    else if (health / maxHealth < 0.5)
    {
        r = 255;
        g = (255 * ((health / maxHealth)));
    }
    else
    {
        r = 255;
        g = 255;
    }

    SDL_SetRenderDrawColor(renderer, r, g, 0, 255);
    rect = {pos.x, pos.y, size.x * (health / maxHealth), size.y};
    SDL_RenderFillRectF(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRectF(renderer, &rect);
}
