#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <Texture.h>
#include <Timer.h>
#include <vector>
#include <algorithm>

class Healthbar
{
private:
    SDL_Renderer *renderer;

    TTF_Font *font;
    SDL_FRect rect;
    float health, maxHealth;
    vector<pair<Texture, Timer>> damageNumbers;

public:
    Healthbar();
    Healthbar(SDL_Renderer *renderer, float health, float maxHealth);
    bool isDead();
    float getHealth();
    void dealDamage(Vector pos, float damage);
    void displayDmgNumbers(Vector offset);
    void displayHealthbar(Vector pos, Vector size);
};